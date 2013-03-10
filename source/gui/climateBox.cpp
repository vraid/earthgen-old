#include "climateBox.h"
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include "planetHandler.h"

ClimateBox::ClimateBox (PlanetHandler* p) : QGroupBox(QString("Climate")), planetHandler(p) {
	form = new QFormLayout();
		seasonsEdit = new QLineEdit();
		form->addRow("Seasons", seasonsEdit);

		axialTiltEdit = new QLineEdit();
		form->addRow("Axial tilt", axialTiltEdit);

		generateButton = new QPushButton("Generate");
		generateButton->setEnabled(false);
		QObject::connect(generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
		form->addWidget(generateButton);
	setLayout(form);
	setValues(Climate_parameters());

	QObject::connect(planetHandler, SIGNAL(terrainCreated()), this, SLOT(enableButton()));
}

void ClimateBox::generateButtonClicked () {
	Climate_parameters par;
	par.seasons = seasonsEdit->text().toInt();
	par.axial_tilt = axialTiltEdit->text().toDouble();

	par.correct_values();
	setValues(par);
	planetHandler->generateClimate(par);
}

void ClimateBox::setValues (const Climate_parameters& par) {
	seasonsEdit->setText(QString::number(par.seasons));
	axialTiltEdit->setText(QString::number((double)par.axial_tilt));
}

void ClimateBox::enableButton () {
	generateButton->setEnabled(true);
}
void ClimateBox::disableButton () {
	generateButton->setEnabled(false);
}