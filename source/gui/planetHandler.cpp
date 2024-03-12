#include "planetHandler.h"
#include "planetWidget.h"
#include <iostream>

PlanetHandler::PlanetHandler () {
	_currentSeason = 0;
}

PlanetHandler::~PlanetHandler () {
}

void PlanetHandler::setCurrentSeason (int n) {
	_currentSeason = std::max(0, n);
}

const Season* PlanetHandler::currentSeason () {
	if (_currentSeason >= planet().climate->seasons.size())
		return nullptr;
	return &nth_season(planet(), _currentSeason);
}

void PlanetHandler::setAxis (const Vector3& v) {
	m_terrain(_planet).var.axis = zero(v) ? default_axis() : normal(v);
	climateDestroyed();
	clear_climate(_planet);
	axisChanged();
}

void PlanetHandler::generateTerrain (const Terrain_parameters& par) {
	climateDestroyed();
	generate_terrain(_planet, par);
	terrainCreated();
	axisChanged();
}

void PlanetHandler::generateClimate (const Climate_parameters& par) {
	generate_climate(_planet, par);
	climateCreated();
}
