#ifndef main_menu_h
#define main_menu_h

#include <QWidget>
class QBoxLayout;

namespace earthgen {

class TerrainBox;
class AxisBox;
class ClimateBox;
class DisplayBox;
class PlanetHandler;
class PlanetWidget;

class MainMenu : public QWidget {
public:
	MainMenu (PlanetHandler*, PlanetWidget*);

	TerrainBox* terrainBox;
	AxisBox* axisBox;
	ClimateBox* climateBox;
	DisplayBox* displayBox;
	QBoxLayout* layout;
	PlanetHandler* planetHandler;
};

}

#endif
