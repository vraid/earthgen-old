#include "generationmenu.h"
#include "gui.h"
#include "../planet/planet.h"

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <QString>
#include <QLabel>

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
		generateButton = new QPushButton("Generate");
		QObject::connect(generateButton, SIGNAL(clicked()), this, SLOT(generate()));
		layout->addRow("", generateButton);
		
		seedEdit = new QLineEdit();
		seedEdit->setText(QString::fromStdString(gui->par->terrain_seed));
		layout->addRow("Seed", seedEdit);
		
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
		
		setAxisButton = new QPushButton("Set axis");
		QObject::connect(setAxisButton, SIGNAL(clicked()), this, SLOT(setAxis()));
		layout->addRow("", setAxisButton);
		
		axisLabel = new QLabel("(0.00, 0.00, 1.00)");
		axisLabel->setAlignment(Qt::AlignCenter);
		layout->addRow("Axis", axisLabel);
		
		coordinateSelectionLabel = new QLabel("(0.00, 0.00, 1.00)");
		coordinateSelectionLabel->setAlignment(Qt::AlignCenter);
		layout->addRow("Selected", coordinateSelectionLabel);
		
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

void GenerationMenu::generate() {
	gui->loadParameters();
	updateParameters();
	gui->resetPlanet();
	gui->generatePlanet();
}

void GenerationMenu::setAxis() {
	gui->par->axis = selectedCoordinate;
	axisLabel->setText(coordinateSelectionLabel->text());
}

void GenerationMenu::setSelectedCoordinate(Vector3 v) {
	selectedCoordinate = v;
	std::ostringstream buffer;
	buffer << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	std::string s = buffer.str();
	coordinateSelectionLabel->setText(QString::fromStdString(s));
}

void GenerationMenu::updateParameters() {
	if (seedEdit->text().isEmpty()) {
		seedEdit->setText(randomSeed());
		gui->par->terrain_seed = seedEdit->text().toStdString();
	}
}
