#include "axisBox.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "planetHandler.h"
#include "planetWidget.h"
#include "util.h"

AxisBox::AxisBox (PlanetHandler* p, PlanetWidget* planetWidget) : QGroupBox("Axis"), planetHandler(p) {
	selected = Vector3(0,0,0);
	form = new QFormLayout();
		axisEdit = new QLineEdit();
		axisEdit->setReadOnly(true);
		axisEdit->setText(string(selected));
		form->addRow("Current", axisEdit);

		selectedEdit = new QLineEdit();
		selectedEdit->setReadOnly(true);
		selectedEdit->setText(string(selected));
		form->addRow("Selected", selectedEdit);

		setButton = new QPushButton("Set");
		setButton->setEnabled(false);
		QObject::connect(setButton, SIGNAL(clicked()), this, SLOT(setButtonClicked()));
		form->addWidget(setButton);
	setLayout(form);

	QObject::connect(planetHandler, SIGNAL(terrainCreated()), this, SLOT(enableButton()));
	QObject::connect(planetHandler, SIGNAL(axisChanged()), this, SLOT(setAxis()));
	QObject::connect(planetWidget, SIGNAL(pointSelected(Vector3)), this, SLOT(setSelection(const Vector3&)));
}

void AxisBox::setButtonClicked () {
	planetHandler->setAxis(selected);
}

void AxisBox::setSelection (const Vector3& v) {
	selected = v;
	selectedEdit->setText(string(selected));
}

void AxisBox::setAxis () {
	axisEdit->setText(string(axis(planetHandler->planet())));
}

void AxisBox::enableButton () {
	setButton->setEnabled(true);
}