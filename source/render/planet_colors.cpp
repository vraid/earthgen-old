#include "planet_colors.h"
#include "../planet/grid/grid.h"
#include "../planet/terrain/terrain.h"
#include "../planet/climate/climate.h"

namespace earthgen {

void clear_colors (Planet_colors& c) {
	std::vector<Color>().swap(c.tiles);
}

void init_colors (Planet_colors& c, const Grid& grid) {
	c.tiles.resize(tile_count(grid));
}

void set_colors (Planet_colors& c, const Grid& grid, const Terrain& terrain, int mode) {
	if (mode == c.TOPOGRAPHY) {
		color_topography(c, grid, terrain);
	}
}

void set_colors (Planet_colors& c, const Grid& grid, const Terrain& terrain, const Season* s, int mode) {
	if (s != nullptr) {
		if (mode == c.VEGETATION) {
			color_vegetation(c, grid, terrain, *s);
		}
		if (mode == c.TEMPERATURE) {
			color_temperature(c, grid, *s);
		}
		else if (mode == c.ARIDITY) {
			color_aridity(c, grid, terrain, *s);
		}
		else if (mode == c.HUMIDITY) {
			color_humidity(c, grid, terrain, *s);
		}
		else if (mode == c.PRECIPITATION) {
			color_precipitation(c, grid, terrain, *s);
		}
	}
	set_colors(c, grid, terrain, mode);
}

void color_topography (Planet_colors& c, const Grid& grid, const Terrain& terrain) {
	static const Color water_deep = Color(0.0, 0.0, 0.25);
	static const Color water = Color(0.0, 0.12, 0.5);
	static const Color water_shallow = Color(0.0, 0.4, 0.6);

	static const Color land[6] = {
		Color(0.0, 0.4, 0.0),
		Color(0.0, 0.7, 0.0),
		Color(1.0, 1.0, 0.0),
		Color(1.0, 0.5, 0.0),
		Color(0.7, 0.0, 0.0),
		Color(0.1, 0.1, 0.1)};
	double land_limits[7] = {-500, 0, 500, 1000, 1500, 2000, 2500};
	for (const Tile& t : tiles(grid)) {
		const Terrain_tile& ter = nth_tile(terrain, id(t));
		double elev = elevation(ter) - sea_level(terrain);
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

void color_vegetation (Planet_colors& c, const Grid& grid, const Terrain& terrain, const Season& s) {
	static const Color snow = Color(1.0, 1.0, 1.0);
	static const Color water_deep = Color(0.05, 0.05, 0.20);
	static const Color water_shallow = Color(0.04, 0.22, 0.42);
	static const Color land_low = Color(0.95, 0.81, 0.53);
	static const Color land_high = Color(0.1, 0.1, 0.1);
	static const Color vegetation = Color(0.176, 0.32, 0.05);

	for (const Tile& t : tiles(grid)) {
		if (is_water(nth_tile(terrain ,id(t)))) {
			double d = std::min(1.0, water_depth(nth_tile(terrain, id(t)))/400);
			c.tiles[id(t)] = interpolate(water_shallow, water_deep, d);
		}
		else {
			auto& climate = nth_tile(s, id(t));
			if (temperature(climate) <= freezing_point())
				c.tiles[id(t)] = snow;
			else {
				double d = std::min(1.0, (elevation(nth_tile(terrain, id(t))) - sea_level(terrain))/2500);
				Color ground = interpolate(land_low, land_high, d);
				double v = std::min(1.0, aridity(climate)/1.5f);
				c.tiles[id(t)] = interpolate(vegetation, ground, v);
			}
		}
	}
}

void color_temperature (Planet_colors& c, const Grid& grid, const Season& s) {
	static const Color col[8] = {
		Color(1.0, 1.0, 1.0),
		Color(0.7, 0, 0.5),
		Color(0, 0, 0.5),
		Color(0, 0, 1.0),
		Color(0, 1.0, 1.0),
		Color(1.0, 1.0, 0),
		Color(1.0, 0.1, 0),
		Color(0.45, 0, 0)};
	static double limits[8] = {-50, -35, -20, -10, 0, 10, 20, 30};

	for (const Tile& t : tiles(grid)) {
		double temp = temperature(nth_tile(s, id(t))) - freezing_point();
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

void color_aridity (Planet_colors& c, const Grid& grid, const Terrain& terrain, const Season& s) {
	static const Color water = Color(1.0, 1.0, 1.0);

	static const Color col[4] = {
		Color(1.0, 0.0, 0.0),
		Color(1.0, 1.0, 0.0),
		Color(0.0, 1.0, 0.0),
		Color(0.0, 0.5, 0.0)};
		
	double limits[4] = {2.0, 1.0, 0.5f, 0.0};

	for (const Tile& t : tiles(grid)) {
		if (is_water(nth_tile(terrain ,id(t))))
			c.tiles[id(t)] = water;
		else {
			double ar = aridity(nth_tile(s, id(t)));
			c.tiles[id(t)] = col[3];
			for (int i=1; i<4; i++) {
				if (ar > limits[i]) {
					double d = std::min(1.0, (ar - limits[i]) / (limits[i-1] - limits[i]));
					c.tiles[id(t)] = interpolate(col[i], col[i-1], d);
					break;
				}
			}
		}
	}
}

void color_humidity (Planet_colors& c, const Grid& grid, const Terrain& terrain, const Season& s) {
	static const Color water = Color(1.0, 1.0, 1.0);
	static const Color land_dry = Color(1.0, 1.0, 0.5);
	static const Color land_mid = Color(1.0, 1.0, 0.0);
	static const Color land_humid = Color(0.0, 0.7, 0.0);
	
	for (const Tile& t : tiles(grid)) {
		double h = humidity(nth_tile(s, id(t))) / saturation_humidity(temperature(nth_tile(s, id(t))));
		if (is_water(nth_tile(terrain, id(t)))) {
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

void color_precipitation (Planet_colors& c, const Grid& grid, const Terrain& terrain, const Season& s) {
	static const Color water = Color(1.0, 1.0, 1.0);
	static const Color dry = Color(1.0, 1.0, 0.5);
	static const Color medium = Color(0.0, 1.0, 0.0);
	static const Color wet = Color(0.0, 0.0, 1.0);

	for (const Tile& t : tiles(grid)) {
		double high = 7e-8;
		double low = high/10;
		if (is_water(nth_tile(terrain, id(t))))
			c.tiles[id(t)] = water;
		else {
			double prec = precipitation(nth_tile(s, id(t)));
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

}
