#include <QBoxLayout>
#include "mainWindow.h"

namespace earthgen {

MainWindow::MainWindow () {
	planetHandler = new PlanetHandler();
	QBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(2, 2, 2, 2);
		planetWidget = new PlanetWidget(planetHandler);
		planetWidget->setMinimumSize(400,400);
		planetWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		mainMenu = new MainMenu(planetHandler, planetWidget);
		layout->addWidget(mainMenu);
		layout->addWidget(planetWidget, 1);

	resize(860,600);
}

}
