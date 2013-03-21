#include "climate_generation.h"
#include "../../math/matrix2.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void generate_climate (Planet& planet, const Climate_parameters& par) {
	clear_climate(planet);
	m_terrain(planet).var.axial_tilt = par.axial_tilt;
	m_climate(planet).var.season_count = par.seasons;
	std::cout << "seasons: ";
	for (int i=0; i<par.seasons; i++) {
		std::cout << i << std::flush;
		generate_season(planet, par, (float)i/par.seasons);
		std::cout << ", ";
	}
	std::cout << "done\n";
}

void copy_season (const Climate_generation_season& from, Season& to) {
	for (unsigned i=0; i<from.tiles.size(); i++) {
		to.tiles[i].temperature = from.tiles[i].temperature;
		to.tiles[i].humidity = from.tiles[i].humidity;
		to.tiles[i].precipitation = from.tiles[i].precipitation;
	}
	for (unsigned i=0; i<from.edges.size(); i++) {
		to.edges[i].wind_velocity = from.edges[i].wind_velocity;
	}
}

void generate_season (Planet& planet, const Climate_parameters& par, float time_of_year) {
	Climate_generation_season season;
	season.tiles.resize(tile_count(planet));
	season.corners.resize(corner_count(planet));
	season.edges.resize(edge_count(planet));

	season.var.time_of_year = time_of_year;
	season.var.solar_equator = axial_tilt(planet) * sin(2.0*pi*time_of_year);
	season.tropical_equator = 0.67*season.var.solar_equator;
	
	_set_temperature(planet, par, season);
	_set_wind(planet, par, season);
	_set_humidity(planet, par, season);
//	_set_river_flow(planet, par, season);
	
	Season s;
	s.tiles.resize(tile_count(planet));
	s.corners.resize(corner_count(planet));
	s.edges.resize(edge_count(planet));
	copy_season(season, s);
	m_climate(planet).seasons.push_back(s);
}

void _set_temperature (const Planet& planet, const Climate_parameters&, Climate_generation_season& season) {
	auto temperature_at_latitude = [](float latitude) {
		return freezing_point() - 25 + 50*cos(latitude);
	};
	
	for (auto& t : tiles(planet)) {
		float temperature = temperature_at_latitude(season.tropical_equator - latitude(planet, vector(t)));
		if (is_land(nth_tile(terrain(planet), id(t)))) {
			if (elevation(nth_tile(terrain(planet), id(t))) > sea_level(planet))
				temperature -= temperature_lapse(elevation(nth_tile(terrain(planet), id(t))) - sea_level(planet));
		}
		else {
			temperature = 0.3*temperature + 0.7*temperature_at_latitude(latitude(planet, vector(t)));
		}
		season.tiles[id(t)].temperature = temperature;
	}
}

Vector2 _default_pressure_gradient_force (double tropical_equator, double latitude) {
	double pressure_derivate = 0.0;
	double pressure_deviation = 20.0 / 15000;
	if (latitude > tropical_equator) {
		double c = 3.0 * pi / (pi / 2.0 - tropical_equator);
		pressure_derivate = pressure_deviation * std::sin(c * (latitude - tropical_equator));
	}
	else {
		double c = 3.0 * pi / (pi / 2.0 + tropical_equator);
		pressure_derivate = pressure_deviation * std::sin(c * (latitude - tropical_equator));
	}
	if (latitude < tropical_equator + (pi/2.0 - tropical_equator)/3.0 && latitude > tropical_equator - (pi/2.0 + tropical_equator)/3.0) {
		pressure_derivate = pressure_derivate / 3.0;
	}
	return Vector2(-pressure_derivate, 0.0);
}

Wind _prevailing_wind (Vector2 pressure_gradient_force, double coriolis_coefficient, double friction_coefficient) {
	double angle_offset = std::atan2(coriolis_coefficient, friction_coefficient);
	double speed = length(pressure_gradient_force) / length(Vector2(coriolis_coefficient, friction_coefficient));
	Vector2 v = rotation_matrix(angle(pressure_gradient_force) - angle_offset) * Vector2(1.0, 0.0);
	Wind w;
	w.speed = speed;
	w.direction = std::atan2(v.y, v.x);
	return w;
}

Wind _default_wind (const Planet& p, int i, double tropical_equator) {
	Vector2 pressure_force = _default_pressure_gradient_force(tropical_equator, latitude(p, vector(nth_tile(p,i))));
	double coriolis_coeff = coriolis_coefficient(p, latitude(p, vector(nth_tile(p,i))));
	double friction = is_land(nth_tile(terrain(p), i)) ? 0.000045 : 0.000045;
	return _prevailing_wind(pressure_force, coriolis_coeff, friction);
}

void _set_wind (const Planet& planet, const Climate_parameters&, Climate_generation_season& season) {
	for (auto& t : tiles(planet)) {
		season.tiles[id(t)].wind = _default_wind(planet, id(t), season.tropical_equator);
		season.tiles[id(t)].wind.direction += north(planet, &t);
	}
	for (auto& t : tiles(planet)) {
		//tile shape in 2d, rotated according to wind direction
		std::vector<Vector2> corners =
			rotation_matrix(north(planet, &t) - season.tiles[id(t)].wind.direction) * polygon(&t, rotation_to_default(planet));

		int e = edge_count(t);
		for (int k=0; k<e; k++) {
			int direction = sign(nth_edge(t, k), &t);
			if (corners[k].x + corners[(k+1)%e].x < 0) direction *= -1;
			season.edges[id(nth_edge(t, k))].wind_velocity -=
				0.5 * direction
				* season.tiles[id(t)].wind.speed
				* std::abs(corners[k].y - corners[(k+1)%e].y)
				/ length(corners[k] - corners[(k+1)%e]);
		}
	}
}

float _air_flow_volume (const Planet& planet, const Edge* e, float wind_velocity) {
	float atmosphere_volume_scale = 100.0;
	float flow = length(planet, e) * wind_velocity * atmosphere_volume_scale;
	if (flow < 0.0) flow *= -1;
	return flow;
}

float _incoming_wind (const Planet& planet, const Climate_generation_season& season, int i) {
	float sum = 0.0;
	const Tile* t = nth_tile(planet, i);
	for (auto& e : edges(t)) {
		if (sign(e, t) * season.edges[id(e)].wind_velocity > 0) {
			sum +=
				std::abs(season.edges[id(e)].wind_velocity)
				* length(planet, e);
		}
	}
	return sum;
}

float _outgoing_wind (const Planet& planet, const Climate_generation_season& season, int i) {
	float sum = 0.0;
	const Tile* t = nth_tile(planet, i);
	for (auto& e : edges(t)) {
		if (sign(e, t) * season.edges[id(e)].wind_velocity < 0) {
			sum +=
				std::abs(season.edges[id(e)].wind_velocity)
				* length(planet, e);
		}
	}
	return sum;
}

float _incoming_humidity (const Planet& planet, const Climate_generation_season& season, int i) {
	float humidity = 0.0;
	const Tile* t = nth_tile(planet, i);
	for (int k=0; k<edge_count(t); k++) {
		const Edge* e = nth_edge(t, k);
		if (sign(e, t) * season.edges[id(e)].wind_velocity > 0) {
			humidity +=
				season.tiles[id(nth_tile(t, k))].humidity
				* std::abs(season.edges[id(e)].wind_velocity)
				* length(planet, e);
		}
	}
	return humidity;
}

float _humidity_change (float first, float second) {
	float near_zero = 1.0e-15;
	if (first < near_zero) {
		if (second > near_zero) return 1.0;
		else return 0.0;
	}
	return 1.0f - first/second;
}

void _iterate_humidity (const Planet& planet, const Climate_parameters& par, Climate_generation_season& season) {
	std::deque<float> humidity;
	std::deque<float> precipitation;
	humidity.resize(tile_count(planet));
	precipitation.resize(tile_count(planet));
	
	float delta = 1.0;
	while (delta > par.error_tolerance) {
//		std::cout << "delta: " << delta << "\n";
		for (int i=0; i<tile_count(planet); i++) {
			precipitation[i] = 0.0;
			if (is_land(nth_tile(terrain(planet), i))) {
				humidity[i] = 0.0;
				precipitation[i] = 0.0;
				float incoming_wind = _incoming_wind(planet, season, i);
				float outgoing_wind = _outgoing_wind(planet, season, i);
				if (incoming_wind > 0.0) {
					float convection = outgoing_wind - incoming_wind;
					float incoming_humidity = _incoming_humidity(planet, season, i);
					// less humidity when incoming wind is less than outgoing
					float density = convection > 0 ?
						incoming_humidity / (incoming_wind + convection) :
						incoming_humidity / incoming_wind;
					float saturation = saturation_humidity(season.tiles[i].temperature);
					// limit to saturation humidity
					humidity[i] = std::min(saturation, density);
					if (saturation < density)
						precipitation[i] += (density - saturation) * incoming_wind;
					// increase humidity when outgoing wind is less than incoming
					if (convection < 0) {
						float convective = humidity[i] * (-convection / incoming_wind);
						if (humidity[i] + convective > saturation)
							precipitation[i] += (humidity[i] + convective - saturation) * (-convection);
						humidity[i] = std::min(saturation, humidity[i] + convective);
					}
				}
				// scale by constant and area
				precipitation[i] *= 3.0 / area(planet, nth_tile(planet, i));
			}
			else
				humidity[i] = season.tiles[i].humidity;
		}
		float largest_change = 0.0;
		for (int i=0; i<tile_count(planet); i++) {
			largest_change = std::max(largest_change, _humidity_change(season.tiles[i].humidity, humidity[i]));
		}
		delta = largest_change;
		for (int i=0; i<tile_count(planet); i++) {
			season.tiles[i].humidity = humidity[i];
			season.tiles[i].precipitation = precipitation[i];
		}
	}
}

void _set_humidity (const Planet& planet, const Climate_parameters& par, Climate_generation_season& season) {
	for (auto& t : tiles(planet)) {
		float humidity = 0.0;		
		if (is_water(nth_tile(terrain(planet), id(t)))) {
			humidity = saturation_humidity(season.tiles[id(t)].temperature);
		}
		season.tiles[id(t)].humidity = humidity;
	}
	_iterate_humidity(planet, par, season);
}

int _lowest_corner (const Planet&, const Tile&) {
	return 0;
}

void _set_river_flow (const Planet&, const Climate_parameters&, Climate_generation_season&) {
	/*
	for (auto& t : tiles(planet)) {
		lowest_corner(t).river_flow_increase += t.precipitation;
	}
	std::multimap<int, const Corner*> river_sources;
	for c : corners {
		if distance_to_sea(c) > 0
			river_sources.insert(-distance_to_sea(c), c);
	}
	for c : river_sources {
		float flow = 0;
		flow += climate_generation_corner(id(c)).river_flow_increase
		if corner has river behind it..
		flow += edge.river_flow;
		climate_generation_edge(river_direction(c)).river_flow = flow;
	}
	*/
}