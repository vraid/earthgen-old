#ifndef main_window_h
#define main_window_h

#include <QWidget>
#include "mainMenu.h"
#include "planetWidget.h"
#include "planetHandler.h"

namespace earthgen {

class MainWindow : public QWidget {
public:
	MainWindow ();

	MainMenu* mainMenu;
	PlanetWidget* planetWidget;
	PlanetHandler* planetHandler;
};

}

#endif
