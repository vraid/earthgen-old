#include "displayBox.h"

#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include "planetHandler.h"
#include "planetWidget.h"
#include "../render/planet_colors.h"
#include <iostream>

namespace earthgen {

DisplayBox::DisplayBox (PlanetHandler* p, PlanetWidget* w) : QGroupBox(QString("Display")), planetHandler(p), planetWidget(w) {
	layout = new QGridLayout();
		mapButton = new QPushButton("Map");
		mapButton->setCheckable(true);
		mapButton->setEnabled(false);
		QObject::connect(mapButton, SIGNAL(clicked()), this, SLOT(mapButtonClicked()));
		layout->addWidget(mapButton, 0, 0, 1, 2);
		
		globeButton = new QPushButton("Globe");
		globeButton->setCheckable(true);
		globeButton->setEnabled(false);
		QObject::connect(globeButton, SIGNAL(clicked()), this, SLOT(globeButtonClicked()));
		layout->addWidget(globeButton, 0, 2, 1, 2);

		layout->addWidget(new QLabel("Color:"), 1, 0, 1, 1, Qt::AlignRight);
		colorBox = new QComboBox();
		colorBox->insertItem(0, "Topography");
		colorBox->setEnabled(false);
		QObject::connect(colorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(colorChanged()));
		layout->addWidget(colorBox, 1, 1, 1, 3);

		layout->addWidget(new QLabel("Season:"), 2, 0, 1, 1, Qt::AlignRight);
		seasonEdit = new QLineEdit();
		seasonEdit->setReadOnly(true);
		layout->addWidget(seasonEdit, 2, 1, 1, 1);
		
		QGridLayout* seasonButtonLayout = new QGridLayout();
			decrementSeasonButton = new QPushButton("<");
			decrementSeasonButton->setEnabled(false);
			QObject::connect(decrementSeasonButton, SIGNAL(clicked()), this, SLOT(decrementSeason()));
			seasonButtonLayout->addWidget(decrementSeasonButton, 0, 0, 1, 1);
			incrementSeasonButton = new QPushButton(">");
			incrementSeasonButton->setEnabled(false);
			QObject::connect(incrementSeasonButton, SIGNAL(clicked()), this, SLOT(incrementSeason()));
			seasonButtonLayout->addWidget(incrementSeasonButton, 0, 1, 1, 1);
		layout->addLayout(seasonButtonLayout, 2, 2, 1, 1);
	setLayout(layout);

	terrainEnabled = false;
	climateEnabled = false;

	QObject::connect(planetHandler, SIGNAL(terrainCreated()), this, SLOT(enableTerrain()));
	QObject::connect(planetHandler, SIGNAL(climateCreated()), this, SLOT(enableClimate()));
	QObject::connect(planetHandler, SIGNAL(climateDestroyed()), this, SLOT(disableClimate()));
}

void DisplayBox::mapButtonClicked () {
	mapButton->setChecked(true);
	globeButton->setChecked(false);
	planetWidget->activateMapRenderer();
	planetWidget->update();
}
void DisplayBox::globeButtonClicked () {
	mapButton->setChecked(false);
	globeButton->setChecked(true);
	planetWidget->activateGlobeRenderer();
	planetWidget->update();
}

void DisplayBox::colorChanged () {
	set_colors(*planetWidget->colors, planetHandler->grid(), planetHandler->terrain(), planetHandler->currentSeason(), colorBox->currentIndex());
	planetWidget->update();
}

void DisplayBox::enableTerrain () {
	mapButton->setEnabled(true);
	globeButton->setEnabled(true);
	colorBox->setCurrentIndex(0);
	colorBox->setEnabled(true);
	if (!terrainEnabled)
		globeButtonClicked();
	terrainEnabled = true;
}
void DisplayBox::enableClimate () {
	if (!climateEnabled) {
		currentSeason = 0;
		seasonEdit->setText("0");
		decrementSeasonButton->setEnabled(true);
		incrementSeasonButton->setEnabled(true);
		colorBox->insertItem(1, "Vegetation");
		colorBox->insertItem(2, "Temperature");
		colorBox->insertItem(3, "Aridity");
		colorBox->insertItem(4, "Humidity");
		colorBox->insertItem(5, "Precipitation");
		colorBox->setCurrentIndex(1);
	}
	climateEnabled = true;
	if (currentSeason >= season_count(planetHandler->climate()))
		currentSeason = 0;
	setSeason(currentSeason);
}
void DisplayBox::disableClimate () {
	seasonEdit->setText("");
	decrementSeasonButton->setEnabled(false);
	incrementSeasonButton->setEnabled(false);
	colorBox->setCurrentIndex(0);
	int removeFrom = 1;
	while (colorBox->count() > removeFrom)
		colorBox->removeItem(removeFrom);
	climateEnabled = false;
}

void DisplayBox::setSeason (int s) {
	currentSeason = s;
	planetHandler->setCurrentSeason(currentSeason);
	seasonEdit->setText(QString::number(currentSeason));
	colorChanged();
}

void DisplayBox::incrementSeason () {
	setSeason((currentSeason+1) % season_count(planetHandler->climate()));
}

void DisplayBox::decrementSeason () {
	setSeason(currentSeason - 1 < 0 ? season_count(planetHandler->climate()) - 1 : currentSeason - 1);
}

}
