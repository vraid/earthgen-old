#ifndef planet_handler_h
#define planet_handler_h

#include <QObject>
#include "../math/vector3.h"
#include "../planet/planet.h"
#include "../planet/terrain/terrain_generation.h"
#include "../planet/climate/climate_generation.h"

class PlanetHandler : public QObject {
	Q_OBJECT
public:
	PlanetHandler ();
	~PlanetHandler ();

	const Planet& planet () const {return _planet;}
	const Season* currentSeason ();
	void setCurrentSeason (int);
public slots:
	void setAxis (Vector3);
	void generateTerrain (const Terrain_parameters&);
	void generateClimate (const Climate_parameters&);
signals:
	void axisChanged ();
	void terrainCreated ();
	void climateCreated ();
	void climateDestroyed ();

private:
	Planet _planet;
	unsigned _currentSeason;
};

#endif