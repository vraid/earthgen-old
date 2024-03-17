#include "terrainBox.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "planetHandler.h"
#include "util.h"

namespace earthgen {

TerrainBox::TerrainBox (PlanetHandler* p) : QGroupBox("Terrain"), planetHandler(p) {
	form = new QFormLayout();
		seedEdit = new QLineEdit();
		form->addRow("Seed:", seedEdit);
		
		gridSizeEdit = new QLineEdit();
		form->addRow("Grid size:", gridSizeEdit);

		iterationsEdit = new QLineEdit();
		form->addRow("Iterations:", iterationsEdit);

		waterRatioEdit = new QLineEdit();
		form->addRow("Water ratio:", waterRatioEdit);
		
		generateButton = new QPushButton("Generate");
		QObject::connect(generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
		form->addWidget(generateButton);
	setLayout(form);
	int default_grid_size = 6;
	setValues(Terrain_parameters(), default_grid_size);
}

void TerrainBox::generateButtonClicked () {
	Terrain_parameters par;
	if (noSeed()) seedEdit->setText(randomAlpha(8));
	par.seed = seedEdit->text().toStdString();
	int grid_size = std::max(0, gridSizeEdit->text().toInt());
	par.iterations = iterationsEdit->text().toInt();
	par.water_ratio = waterRatioEdit->text().toDouble();

	par.correct_values();
	setValues(par, grid_size);
	planetHandler->setGridSize(grid_size);
	planetHandler->generateTerrain(par);
}

bool TerrainBox::noSeed () {
	return seedEdit->text().length() == 0;
}

void TerrainBox::setValues (const Terrain_parameters& par, int grid_size) {
	gridSizeEdit->setText(QString::number(grid_size));
	iterationsEdit->setText(QString::number(par.iterations));
	waterRatioEdit->setText(QString::number(par.water_ratio));
}

}
