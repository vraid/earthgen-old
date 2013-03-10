#include "mainMenu.h"
#include <QBoxLayout>
#include "terrainBox.h"
#include "axisBox.h"
#include "climateBox.h"
#include "displayBox.h"
#include "planetHandler.h"

MainMenu::MainMenu (PlanetHandler* p, PlanetWidget* planetWidget) : planetHandler(p) {
	layout = new QBoxLayout(QBoxLayout::TopToBottom);
	layout->setAlignment(Qt::AlignTop);
		terrainBox = new TerrainBox(planetHandler);
		terrainBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		layout->addWidget(terrainBox);

		axisBox = new AxisBox(planetHandler, planetWidget);
		axisBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		layout->addWidget(axisBox);

		climateBox = new ClimateBox(planetHandler);
		climateBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		layout->addWidget(climateBox);

		displayBox = new DisplayBox(planetHandler, planetWidget);
		displayBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
		layout->addWidget(displayBox);
	setLayout(layout);
	setMinimumWidth(200);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
}