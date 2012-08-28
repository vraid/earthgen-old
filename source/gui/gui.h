#ifndef gui_h
#define gui_h

class GUI;
class GLWidget;
class QLabel;

#include <iostream>
#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QCheckBox>

class Planet;
class Parameters;
class Projection;

class GUI {
public:
	GUI();
	~GUI();
private:
	static void generateAction(GUI*);
	static void displayMode(GUI*,int);
	static void nextSeasonAction(GUI*);
public:
	QWidget* window;
	QHBoxLayout* windowLayout;
	GLWidget* glwin;

	Planet* p;
	Parameters* par;
	Projection* proj;
};

#endif
