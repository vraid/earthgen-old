#ifndef gui_h
#define gui_h

#include <iostream>
#include <string>
#include <QString>
#include "../planet/parameters.h"

class QWidget;
class QLayout;
class QGridLayout;

class GenerationMenu;
class GLWidget;
class Planet;
class Parameters;
class Projection;

class GUI {
public:
	GUI();
	~GUI();
private:
	static void generateAction (GUI*);
	static void displayMode (GUI*,int);
	static void nextSeasonAction (GUI*);
public:

	void loadParameters();
	void resetPlanet();
	void generatePlanet();

	QWidget* window;
	QGridLayout* windowLayout;
	GenerationMenu* sideMenu;
	GLWidget* glwin;

	Planet* p;
	Parameters* par;
	Projection* proj;
};

#endif
