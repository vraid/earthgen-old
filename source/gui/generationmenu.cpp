#include "generationmenu.h"
#include "gui.h"
#include "../planet/planet.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <QString>
#include <QLabel>

#include <QDoubleValidator>
#include <QFormLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

GenerationMenu::GenerationMenu (GUI* g) {
	gui = g;

	setMinimumWidth(200);
	setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Ignored);
	layout = new QFormLayout();
	layout->setAlignment(Qt::AlignTop);
		generateTerrainButton = new QPushButton("Generate terrain");
		QObject::connect(generateTerrainButton, SIGNAL(clicked()), this, SLOT(generateTerrain()));
		layout->addRow("", generateTerrainButton);
		
		seedEdit = new QLineEdit();
		seedEdit->setText(QString::fromStdString(gui->par->terrain_seed));
		layout->addRow("Seed", seedEdit);
		oldSeed = seedEdit->text().toStdString();
		
		iterationEdit = new QLineEdit();
		iterationValidator = new QIntValidator(iterationEdit);
		iterationValidator->setBottom(1);
		iterationEdit->setValidator(iterationValidator);
		iterationEdit->setText(QString::number(gui->par->iterations));
		layout->addRow("Iterations", iterationEdit);
		
		gridSizeEdit = new QLineEdit();
		gridSizeValidator = new QIntValidator(gridSizeEdit);
		gridSizeValidator->setRange(0,11);
		gridSizeEdit->setValidator(gridSizeValidator);
		gridSizeEdit->setText(QString::number(gui->par->grid_size));
		layout->addRow("Grid size", gridSizeEdit);

		waterRatioEdit = new QLineEdit();
		waterRatioValidator = new QDoubleValidator(waterRatioEdit);
		waterRatioValidator->setRange(0.05, 0.95, 5);
		waterRatioEdit->setValidator(waterRatioValidator);
		waterRatioEdit->setText(QString::number(gui->par->water_ratio));
		layout->addRow("Water ratio", waterRatioEdit);
		
		setAxisButton = new QPushButton("Set axis");
		QObject::connect(setAxisButton, SIGNAL(clicked()), this, SLOT(setAxis()));
		layout->addRow("", setAxisButton);
		
		axisLabel = new QLabel("(0.00, 0.00, 1.00)");
		axisLabel->setAlignment(Qt::AlignCenter);
		layout->addRow("Axis", axisLabel);
		
		coordinateSelectionLabel = new QLabel("(0.00, 0.00, 1.00)");
		coordinateSelectionLabel->setAlignment(Qt::AlignCenter);
		layout->addRow("Selected", coordinateSelectionLabel);
		
		generateClimateButton = new QPushButton("Generate climate");
		QObject::connect(generateClimateButton, SIGNAL(clicked()), this, SLOT(generateClimate()));
		layout->addRow("", generateClimateButton);
		
		seasonsEdit = new QLineEdit();
		seasonsValidator = new QIntValidator(seasonsEdit);
		seasonsValidator->setBottom(1);
		seasonsEdit->setValidator(seasonsValidator);
		seasonsEdit->setText(QString::number(gui->par->seasons));
		layout->addRow("Seasons", seasonsEdit);
	setLayout(layout);
}

QString GenerationMenu::randomSeed() {
	return QString::fromStdString(randomString(10));
}

std::string GenerationMenu::randomString(int length) {
	static char alphanum[] =
		"0123456789"
		"abcdefghijklmnopqrstuvwxyz";
	std::string str;
	str.resize(length);
	srand(time(NULL));
	for (int i=0; i<length; i++) {
		str[i] = alphanum[rand()%36];
	}
	return str;
}

void GenerationMenu::generateTerrain() {
	gui->loadParameters();
	updateTerrainParameters();
	gui->resetPlanet();
	gui->generateTerrain();
}

void GenerationMenu::generateClimate() {
	updateClimateParameters();
	gui->generateClimate();
}

void GenerationMenu::setAxis() {
	axis = selectedCoordinate;
	axisLabel->setText(coordinateSelectionLabel->text());
}

QString GenerationMenu::vectorToString(Vector3 v) {
	std::ostringstream buffer;
	buffer << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	std::string s = buffer.str();
	return QString::fromStdString(s);
}

void GenerationMenu::setSelectedCoordinate(Vector3 v) {
	selectedCoordinate = v;
	coordinateSelectionLabel->setText(vectorToString(v));
}

void GenerationMenu::resetAxis() {
	Vector3 v = Vector3(0,0,1);
	axis = v;
	oldRotation = Quaternion();
	selectedCoordinate = v;
	gui->par->axis = v;
	axisLabel->setText(vectorToString(v));
	coordinateSelectionLabel->setText(vectorToString(v));
}

void GenerationMenu::updateTerrainParameters() {
	if (seedEdit->text().isEmpty()) {
		seedEdit->setText(randomSeed());
	}
	if (oldSeed.compare(seedEdit->text().toStdString()) != 0) {
		resetAxis();
	}
	oldSeed = seedEdit->text().toStdString();
	gui->par->terrain_seed = seedEdit->text().toStdString();

	gui->par->iterations = iterationEdit->text().toInt();

	gui->par->grid_size = gridSizeEdit->text().toInt();

	axis = quaternion::conjugate(oldRotation)*axis;
	gui->par->axis = axis;
	if (axis.z == 1) {
		oldRotation = Quaternion();
	}
	else {
		if (axis.z == -1) oldRotation = Quaternion(pi, Vector3(1,0,0));
		else              oldRotation = Quaternion(axis, Vector3(0,0,1));
	}
	gui->par->rotation = oldRotation;

	gui->par->water_ratio = std::min(std::max(waterRatioEdit->text().toDouble(), waterRatioValidator->bottom()), waterRatioValidator->top());
	waterRatioEdit->setText(QString::number(gui->par->water_ratio));
}

void GenerationMenu::updateClimateParameters() {
	gui->par->seasons = seasonsEdit->text().toInt();
}
