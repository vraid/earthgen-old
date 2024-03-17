#include "planetHandler.h"
#include "planetWidget.h"
#include "../planet/grid/create_grid.h"

namespace earthgen {

PlanetHandler::PlanetHandler () {
	currentSeason_ = 0;
	Grid* grid = new Grid();
	size_0_grid(*grid);
	grids.push_back(std::unique_ptr<Grid>(grid));
}

PlanetHandler::~PlanetHandler () {
}

void PlanetHandler::setCurrentSeason (int n) {
	currentSeason_ = std::max(0, n);
}

const Season* PlanetHandler::currentSeason () {
	if (currentSeason_ >= climate().seasons.size()) {
		return nullptr;
	}
	return &nth_season(climate(), currentSeason_);
}

void PlanetHandler::setAxis (const Vector3& v) {
	terrain_.var.axis = zero(v) ? default_axis() : normal(v);
	climateDestroyed();
	clear_climate(climate_);
	axisChanged();
}

void PlanetHandler::setGridSize(int size) {
	current_grid_size = size;
	while (grids.size() < current_grid_size + 1) {
		Grid* grid = new Grid();
		subdivide(*grid, *(grids.back()));
		grids.push_back(std::unique_ptr<Grid>(grid));
	}
}

void PlanetHandler::generateTerrain (const Terrain_parameters& par) {
	generate_terrain(terrain_, grid(), par);
	clear_climate(climate_);
	terrainCreated();
	climateDestroyed();
	axisChanged();
}

void PlanetHandler::generateClimate (const Climate_parameters& par) {
	climateDestroyed();
	generate_climate(climate_, terrain_, grid(), par);
	climateCreated();
}

}
