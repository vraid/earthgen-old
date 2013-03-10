#include "mainWindow.h"

MainWindow::MainWindow () {
	planetHandler = new PlanetHandler();
	
	layout = new QGridLayout();
		planetWidget = new PlanetWidget(planetHandler);
		mainMenu = new MainMenu(planetHandler, planetWidget);
		layout->addWidget(mainMenu, 0, 0, 2, 1, 0);

		planetWidget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
		layout->addWidget(planetWidget, 0, 1, 2, 1, 0);
	setLayout(layout);
	resize(860,600);
}