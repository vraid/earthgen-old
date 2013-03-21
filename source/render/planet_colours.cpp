#include "planet_colours.h"
#include "../planet/planet.h"

void clear_colours (Planet_colours& c) {
	std::deque<Colour>().swap(c.tiles);
}

void init_colours (Planet_colours& c, const Planet& p) {
	c.tiles.resize(tile_count(p));
}

void set_colours (Planet_colours& c, const Planet& p, int mode) {
	if (mode == c.TOPOGRAPHY)
		colour_topography(c, p);
}

void set_colours (Planet_colours& c, const Planet& p, const Season* s, int mode) {
	if (s != nullptr) {
		if (mode == c.VEGETATION)
			colour_vegetation(c, p, *s);
		if (mode == c.TEMPERATURE)
			colour_temperature(c, p, *s);
		else if (mode == c.ARIDITY)
			colour_aridity(c, p, *s);
		else if (mode == c.HUMIDITY)
			colour_humidity(c, p, *s);
		else if (mode == c.PRECIPITATION)
			colour_precipitation(c, p, *s);
	}
	set_colours(c, p, mode);
}

void colour_topography (Planet_colours& c, const Planet& p) {
	static const Colour water_deep = Colour(0.0, 0.0, 0.25);
	static const Colour water = Colour(0.0, 0.12, 0.5);
	static const Colour water_shallow = Colour(0.0, 0.4, 0.6);

	static const Colour land[6] = {
		Colour(0.0, 0.4, 0.0),
		Colour(0.0, 0.7, 0.0),
		Colour(1.0, 1.0, 0.0),
		Colour(1.0, 0.5, 0.0),
		Colour(0.7, 0.0, 0.0),
		Colour(0.1, 0.1, 0.1)};
	double land_limits[7] = {-500, 0, 500, 1000, 1500, 2000, 2500};
	for (const Tile& t : tiles(p)) {
		const Terrain_tile& ter = nth_tile(terrain(p), id(t));
		double elev = elevation(ter) - sea_level(p);
		if (is_water(ter)) {
			if (elev < -1000) {
				c.tiles[id(t)] = water_deep;
			}
			else if (elev < -500) {
				double d = (elev+500)/(-500);
				c.tiles[id(t)] = interpolate(water, water_deep, d);
			}
			else {
				double d = elev/(-500);
				c.tiles[id(t)] = interpolate(water_shallow, water, d);
			}
		}
		else {
			c.tiles[id(t)] = land[5];
			for (int i=0; i<5; i++) {
				if (elev <= land_limits[i+1]) {
					double d = std::max(0.0, std::min(1.0, (elev - land_limits[i]) / (land_limits[i+1] - land_limits[i])));
					c.tiles[id(t)] = interpolate(land[i], land[i+1], d);
					break;
				}
			}
		}
	}
}

void colour_vegetation (Planet_colours& c, const Planet& p, const Season& s) {
	static const Colour snow = Colour(1.0, 1.0, 1.0);
	static const Colour water_deep = Colour(0.05, 0.05, 0.20);
	static const Colour water_shallow = Colour(0.04, 0.22, 0.42);
	static const Colour land_low = Colour(0.95, 0.81, 0.53);
	static const Colour land_high = Colour(0.1, 0.1, 0.1);
	static const Colour vegetation = Colour(0.176, 0.32, 0.05);

	for (const Tile& t : tiles(p)) {
		if (is_water(nth_tile(terrain(p) ,id(t)))) {
			double d = std::min(1.0f, water_depth(nth_tile(terrain(p), id(t)))/400);
			c.tiles[id(t)] = interpolate(water_shallow, water_deep, d);
		}
		else {
			auto& climate = nth_tile(s, id(t));
			if (temperature(climate) <= freezing_point())
				c.tiles[id(t)] = snow;
			else {
				double d = std::min(1.0, (elevation(nth_tile(terrain(p), id(t))) - sea_level(p))/2500);
				Colour ground = interpolate(land_low, land_high, d);
				double v = std::min(1.0f, aridity(climate)/1.5f);
				c.tiles[id(t)] = interpolate(vegetation, ground, v);
			}
		}
	}
}

void colour_temperature (Planet_colours& c, const Planet& p, const Season& s) {
	static const Colour col[8] = {
		Colour(1.0, 1.0, 1.0),
		Colour(0.7, 0, 0.5),
		Colour(0, 0, 0.5),
		Colour(0, 0, 1.0),
		Colour(0, 1.0, 1.0),
		Colour(1.0, 1.0, 0),
		Colour(1.0, 0.1, 0),
		Colour(0.45, 0, 0)};
	static float limits[8] = {-50, -35, -20, -10, 0, 10, 20, 30};

	for (const Tile& t : tiles(p)) {
		float temp = temperature(nth_tile(s, id(t))) - freezing_point();
		if (temp <= limits[0])
			c.tiles[id(t)] = col[0];
		else if (temp >= limits[7])
			c.tiles[id(t)] = col[7];
		else {
			for (int i=0; i<7; i++) {
				if (temp >= limits[i] && temp < limits[i+1]) {
					double d = (temp - limits[i]) / (limits[i+1] - limits[i]);
					c.tiles[id(t)] = interpolate(col[i], col[i+1], d);
					break;
				}
			}
		}
	}
}

void colour_aridity (Planet_colours& c, const Planet& p, const Season& s) {
	static const Colour water = Colour(1.0, 1.0, 1.0);

	static const Colour col[4] = {
		Colour(1.0, 0.0, 0.0),
		Colour(1.0, 1.0, 0.0),
		Colour(0.0, 1.0, 0.0),
		Colour(0.0, 0.5, 0.0)};
		
	float limits[4] = {2.0f, 1.0f, 0.5f, 0.0f};

	for (const Tile& t : tiles(p)) {
		if (is_water(nth_tile(terrain(p) ,id(t))))
			c.tiles[id(t)] = water;
		else {
			float ar = aridity(nth_tile(s, id(t)));
			c.tiles[id(t)] = col[3];
			for (int i=1; i<4; i++) {
				if (ar > limits[i]) {
					double d = std::min(1.0f, (ar - limits[i]) / (limits[i-1] - limits[i]));
					c.tiles[id(t)] = interpolate(col[i], col[i-1], d);
					break;
				}
			}
		}
	}
}

void colour_humidity (Planet_colours& c, const Planet& p, const Season& s) {
	static const Colour water = Colour(1.0, 1.0, 1.0);
	static const Colour land_dry = Colour(1.0, 1.0, 0.5);
	static const Colour land_mid = Colour(1.0, 1.0, 0.0);
	static const Colour land_humid = Colour(0.0, 0.7, 0.0);
	
	for (const Tile& t : tiles(p)) {
		double h = humidity(nth_tile(s, id(t))) / saturation_humidity(temperature(nth_tile(s, id(t))));
		if (is_water(nth_tile(terrain(p), id(t)))) {
			c.tiles[id(t)] = water;
		}
		else {
			if (h <= 0.5) {
				double d = h / 0.5;
				c.tiles[id(t)] = interpolate(land_dry, land_mid, d);
			}
			else {
				double d = (h-0.5)/0.5;
				c.tiles[id(t)] = interpolate(land_mid, land_humid, d);
			}
		}
	}
}

void colour_precipitation (Planet_colours& c, const Planet& p, const Season& s) {
	static const Colour water = Colour(1.0, 1.0, 1.0);
	static const Colour dry = Colour(1.0, 1.0, 0.5);
	static const Colour medium = Colour(0.0, 1.0, 0.0);
	static const Colour wet = Colour(0.0, 0.0, 1.0);

	for (const Tile& t : tiles(p)) {
		double high = 7e-8;
		double low = high/10;
		if (is_water(nth_tile(terrain(p), id(t))))
			c.tiles[id(t)] = water;
		else {
			float prec = precipitation(nth_tile(s, id(t)));
			if (prec < low) {
				double d = prec / low;
				c.tiles[id(t)] = interpolate(dry, medium, d);
			}
			else {
				double d = std::min(1.0, (prec - low) / (high - low));
				c.tiles[id(t)] = interpolate(medium, wet, d);
			}
		}
	}
}
