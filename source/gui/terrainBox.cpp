#include "terrainBox.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "planetHandler.h"
#include "util.h"

TerrainBox::TerrainBox (PlanetHandler* p) : QGroupBox("Terrain"), planetHandler(p) {
	form = new QFormLayout();
		seedEdit = new QLineEdit();
		form->addRow("Seed", seedEdit);
		
		gridSizeEdit = new QLineEdit();
		form->addRow("Grid size", gridSizeEdit);

		iterationsEdit = new QLineEdit();
		form->addRow("Iterations", iterationsEdit);

		waterRatioEdit = new QLineEdit();
		form->addRow("Water ratio", waterRatioEdit);
		
		generateButton = new QPushButton("Generate");
		QObject::connect(generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
		form->addWidget(generateButton);
	setLayout(form);
	setValues(Terrain_parameters());
}

void TerrainBox::generateButtonClicked () {
	Terrain_parameters par;
	if (noSeed()) seedEdit->setText(randomAlpha(8));
	par.seed = seedEdit->text().toStdString();
	par.grid_size = gridSizeEdit->text().toInt();
	par.iterations = iterationsEdit->text().toInt();
	par.water_ratio = waterRatioEdit->text().toDouble();

	par.correct_values();
	setValues(par);
	planetHandler->generateTerrain(par);
}

bool TerrainBox::noSeed () {
	return seedEdit->text().length() == 0;
}

void TerrainBox::setValues (const Terrain_parameters& par) {
	gridSizeEdit->setText(QString::number(par.grid_size));
	iterationsEdit->setText(QString::number(par.iterations));
	waterRatioEdit->setText(QString::number(par.water_ratio));
}