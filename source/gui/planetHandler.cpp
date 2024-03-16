#include "planetHandler.h"
#include "planetWidget.h"
#include <iostream>

namespace earthgen {

PlanetHandler::PlanetHandler () {
	currentSeason_ = 0;
}

PlanetHandler::~PlanetHandler () {
}

void PlanetHandler::setCurrentSeason (int n) {
	currentSeason_ = std::max(0, n);
}

const Season* PlanetHandler::currentSeason () {
	if (currentSeason_ >= climate().seasons.size())
		return nullptr;
	return &nth_season(climate(), currentSeason_);
}

void PlanetHandler::setAxis (const Vector3& v) {
	terrain_.var.axis = zero(v) ? default_axis() : normal(v);
	climateDestroyed();
	clear_climate(climate_);
	axisChanged();
}

void PlanetHandler::generateTerrain (const Terrain_parameters& par) {
	climateDestroyed();
	clear_climate(climate_);
	generate_terrain(terrain_, grid_, par);
	terrainCreated();
	axisChanged();
}

void PlanetHandler::generateClimate (const Climate_parameters& par) {
	generate_climate(climate_, terrain_, grid_, par);
	climateCreated();
}

}
