#ifndef planet_handler_h
#define planet_handler_h

#include <QObject>
#include "../math/vector3.h"
#include "../planet/grid/grid.h"
#include "../planet/terrain/terrain.h"
#include "../planet/climate/climate.h"
#include "../planet/terrain/terrain_generation.h"
#include "../planet/climate/climate_generation.h"

namespace earthgen {

class PlanetHandler : public QObject {
	Q_OBJECT
public:
	PlanetHandler ();
	~PlanetHandler ();

	const Grid& grid () const {return grid_;};
	const Terrain& terrain () const {return terrain_;};
	const Climate& climate () const {return climate_;};
	const Season* currentSeason ();
	void setCurrentSeason (int);
public slots:
	void setAxis (const Vector3&);
	void generateTerrain (const Terrain_parameters&);
	void generateClimate (const Climate_parameters&);
signals:
	void axisChanged ();
	void terrainCreated ();
	void climateCreated ();
	void climateDestroyed ();

private:
	Grid grid_;
	Terrain terrain_;
	Climate climate_;
	unsigned currentSeason_;
};

}

#endif
