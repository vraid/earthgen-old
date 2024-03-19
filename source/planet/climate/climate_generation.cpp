#include "climate_generation.h"
#include "../grid/grid.h"
#include "../grid/grid_util.h"
#include "../terrain/terrain.h"
#include "climate.h"
#include "../../math/matrix2.h"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace earthgen {

void generate_climate (Climate& climate, Terrain& terrain, const Grid& grid, const Climate_parameters& par) {
	clear_climate(climate);
	terrain.var.axial_tilt = par.axial_tilt;
	climate.var.season_count = par.seasons;
	std::cout << "seasons: ";
	for (int i=0; i<par.seasons; i++) {
		std::cout << i << std::flush;
		generate_season(climate, terrain, grid, par, (1.0*i)/par.seasons);
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

void generate_season (Climate& climate, const Terrain& terrain, const Grid& grid, const Climate_parameters& par, double time_of_year) {
	Climate_generation_season season;
	season.tiles.resize(tile_count(grid));
	season.edges.resize(edge_count(grid));

	season.var.time_of_year = time_of_year;
	season.var.solar_equator = axial_tilt(terrain) * std::sin(2.0*pi*time_of_year);
	season.tropical_equator = 0.67*season.var.solar_equator;
	
	_set_temperature(terrain, grid, par, season);
	_set_wind(terrain, grid, par, season);
	_set_humidity(terrain, grid, par, season);
	
	Season s;
	s.tiles.resize(tile_count(grid));
	s.edges.resize(edge_count(grid));
	copy_season(season, s);
	climate.seasons.push_back(s);
}

void _set_temperature (const Terrain& terrain, const Grid& grid, const Climate_parameters&, Climate_generation_season& season) {
	auto temperature_at_latitude = [](double latitude) {
		return freezing_point() - 25 + 50*std::cos(latitude);
	};
	
	for (auto& t : tiles(grid)) {
		double temperature = temperature_at_latitude(season.tropical_equator - latitude(terrain, vector(t)));
		if (is_land(nth_tile(terrain, id(t)))) {
			if (elevation(nth_tile(terrain, id(t))) > sea_level(terrain))
				temperature -= temperature_lapse(elevation(nth_tile(terrain, id(t))) - sea_level(terrain));
		}
		else {
			temperature = 0.3*temperature + 0.7*temperature_at_latitude(latitude(terrain, vector(t)));
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
	w.direction = std::atan2(v.y(), v.x());
	return w;
}

Wind _default_wind (const Terrain& terrain, const Grid& grid, int i, double tropical_equator) {
	Vector2 pressure_force = _default_pressure_gradient_force(tropical_equator, latitude(terrain, vector(nth_tile(grid,i))));
	double coriolis_coeff = coriolis_coefficient(terrain, latitude(terrain, vector(nth_tile(grid,i))));
	double friction = is_land(nth_tile(terrain, i)) ? 0.000045 : 0.000045;
	return _prevailing_wind(pressure_force, coriolis_coeff, friction);
}

void _set_wind (const Terrain& terrain, const Grid& grid, const Climate_parameters&, Climate_generation_season& season) {
	for (auto& t : tiles(grid)) {
		season.tiles[id(t)].wind = _default_wind(terrain, grid, id(t), season.tropical_equator);
		season.tiles[id(t)].wind.direction += north(terrain, &t);
	}
	for (auto& t : tiles(grid)) {
		//tile shape in 2d, rotated according to wind direction
		std::vector<Vector2> corners =
			rotation_matrix(north(terrain, &t) - season.tiles[id(t)].wind.direction) * polygon(&t, rotation_to_default(terrain));

		for (int k : indices(t)) {
			int direction = sign(nth_edge(t, k), &t);
			if (corners[k].x() + corners[(k+1)%edge_count(t)].x() < 0) direction *= -1;
			season.edges[id(nth_edge(t, k))].wind_velocity -=
				0.5 * direction
				* season.tiles[id(t)].wind.speed
				* std::abs(corners[k].y() - corners[(k+1)%edge_count(t)].y())
				/ length(corners[k] - corners[(k+1)%edge_count(t)]);
		}
	}
}

double _air_flow_volume (const Terrain& terrain, const Edge* e, double wind_velocity) {
	double atmosphere_volume_scale = 100.0;
	double flow = length(terrain, e) * wind_velocity * atmosphere_volume_scale;
	if (flow < 0.0) flow *= -1;
	return flow;
}

double _incoming_wind (const Terrain& terrain, const Grid& grid, const Climate_generation_season& season, int i) {
	double sum = 0.0;
	const Tile* t = nth_tile(grid, i);
	for (auto& e : edges(t)) {
		if (sign(e, t) * season.edges[id(e)].wind_velocity > 0) {
			sum +=
				std::abs(season.edges[id(e)].wind_velocity)
				* length(terrain, e);
		}
	}
	return sum;
}

double _outgoing_wind (const Terrain& terrain, const Grid& grid, const Climate_generation_season& season, int i) {
	double sum = 0.0;
	const Tile* t = nth_tile(grid, i);
	for (auto& e : edges(t)) {
		if (sign(e, t) * season.edges[id(e)].wind_velocity < 0) {
			sum +=
				std::abs(season.edges[id(e)].wind_velocity)
				* length(terrain, e);
		}
	}
	return sum;
}

double _incoming_humidity (const Terrain& terrain, const Grid& grid, const Climate_generation_season& season, int i) {
	double humidity = 0.0;
	const Tile* t = nth_tile(grid, i);
	for (int k : indices(t)) {
		const Edge* e = nth_edge(t, k);
		if (sign(e, t) * season.edges[id(e)].wind_velocity > 0) {
			humidity +=
				season.tiles[id(nth_tile(t, k))].humidity
				* std::abs(season.edges[id(e)].wind_velocity)
				* length(terrain, e);
		}
	}
	return humidity;
}

double _humidity_change (double first, double second) {
	double near_zero = 1.0e-15;
	if (first < near_zero) {
		if (second > near_zero) return 1.0;
		else return 0.0;
	}
	return 1.0 - first/second;
}

void _iterate_humidity (const Terrain& terrain, const Grid& grid, const Climate_parameters& par, Climate_generation_season& season) {
	std::vector<double> humidity;
	std::vector<double> precipitation;
	humidity.resize(tile_count(grid));
	precipitation.resize(tile_count(grid));
	
	double delta = 1.0;
	while (delta > par.error_tolerance) {
//		std::cout << "delta: " << delta << "\n";
		for (int i=0; i<tile_count(grid); i++) {
			precipitation[i] = 0.0;
			if (is_land(nth_tile(terrain, i))) {
				humidity[i] = 0.0;
				precipitation[i] = 0.0;
				double incoming_wind = _incoming_wind(terrain, grid, season, i);
				double outgoing_wind = _outgoing_wind(terrain, grid, season, i);
				if (incoming_wind > 0.0) {
					double convection = outgoing_wind - incoming_wind;
					double incoming_humidity = _incoming_humidity(terrain, grid, season, i);
					// less humidity when incoming wind is less than outgoing
					double density = convection > 0 ?
						incoming_humidity / (incoming_wind + convection) :
						incoming_humidity / incoming_wind;
					double saturation = saturation_humidity(season.tiles[i].temperature);
					// limit to saturation humidity
					humidity[i] = std::min(saturation, density);
					if (saturation < density)
						precipitation[i] += (density - saturation) * incoming_wind;
					// increase humidity when outgoing wind is less than incoming
					if (convection < 0) {
						double convective = humidity[i] * (-convection / incoming_wind);
						if (humidity[i] + convective > saturation)
							precipitation[i] += (humidity[i] + convective - saturation) * (-convection);
						humidity[i] = std::min(saturation, humidity[i] + convective);
					}
				}
				// scale by constant and area
				precipitation[i] *= 3.0 / area(terrain, nth_tile(grid, i));
			}
			else
				humidity[i] = season.tiles[i].humidity;
		}
		double largest_change = 0.0;
		for (int i=0; i<tile_count(grid); i++) {
			largest_change = std::max(largest_change, _humidity_change(season.tiles[i].humidity, humidity[i]));
		}
		delta = largest_change;
		for (int i=0; i<tile_count(grid); i++) {
			season.tiles[i].humidity = humidity[i];
			season.tiles[i].precipitation = precipitation[i];
		}
	}
}

void _set_humidity (const Terrain& terrain, const Grid& grid, const Climate_parameters& par, Climate_generation_season& season) {
	for (auto& t : tiles(grid)) {
		double humidity = 0.0;
		if (is_water(nth_tile(terrain, id(t)))) {
			humidity = saturation_humidity(season.tiles[id(t)].temperature);
		}
		season.tiles[id(t)].humidity = humidity;
	}
	_iterate_humidity(terrain, grid, par, season);
}

int _lowest_corner (const Planet&, const Tile&) {
	return 0;
}

}
