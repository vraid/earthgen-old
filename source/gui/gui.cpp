#include "gui.h"
#include "glwidget.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include <iostream>
#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>

GUI::GUI() {
	p = new Planet();
	par = parameters::load();
	p->par = *par;
	p->grid = grid::create(p->par.grid_size);
	terrain::generate(p);

	proj = new Projection();
	projection::init(p, proj);
	projection::set_colors(proj);
	projection::color_topography(proj);
	
	window = new QWidget();
	windowLayout = new QGridLayout();
		sideMenu = new QWidget();
		sideMenu->setMinimumWidth(200);
		sideMenu->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Ignored);
		sideMenuLayout = new QFormLayout();
		sideMenuLayout->setAlignment(Qt::AlignTop);
			generateButton = new QPushButton("Generate");
			sideMenuLayout->addRow("", generateButton);
			seedEdit = new QLineEdit();
			seedEdit->setText(QString::fromStdString(par->terrain_seed));
			sideMenuLayout->addRow("Seed", seedEdit);
			iterationEdit = new QLineEdit();
			iterationValidator = new QIntValidator(iterationEdit);
			iterationValidator->setBottom(1);
			iterationEdit->setValidator(iterationValidator);
			iterationEdit->setText(QString::number(par->iterations));
			sideMenuLayout->addRow("Iterations", iterationEdit);
			gridSizeEdit = new QLineEdit();
			gridSizeValidator = new QIntValidator(gridSizeEdit);
			gridSizeValidator->setRange(0,11);
			gridSizeEdit->setValidator(gridSizeValidator);
			gridSizeEdit->setText(QString::number(par->grid_size));
			sideMenuLayout->addRow("Grid size", gridSizeEdit);
			setAxisButton = new QPushButton("Set axis");
			sideMenuLayout->addRow("", setAxisButton);
			axisLabel = new QLabel("(0.00, 0.00, 1.00)");
			axisLabel->setAlignment(Qt::AlignCenter);
			sideMenuLayout->addRow("Axis", axisLabel);
			coordinateSelectionLabel = new QLabel("(0.00, 0.00, 1.00)");
			coordinateSelectionLabel->setAlignment(Qt::AlignCenter);
			sideMenuLayout->addRow("Selected", coordinateSelectionLabel);
			seasonsEdit = new QLineEdit();
			seasonsValidator = new QIntValidator(seasonsEdit);
			seasonsValidator->setBottom(1);
			seasonsEdit->setValidator(seasonsValidator);
			seasonsEdit->setText(QString::number(par->seasons));
			sideMenuLayout->addRow("Seasons", seasonsEdit);
		sideMenu->setLayout(sideMenuLayout);
		windowLayout->addWidget(sideMenu, 0, 0, 2, 1, 0);
		glwin = new GLWidget(window);
		glwin->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
		glwin->gui = this;
		windowLayout->addWidget(glwin, 0, 1, 2, 1, 0);
	window->setLayout(windowLayout);
	window->resize(1024,600);
	window->show();
}

GUI::~GUI() {
	delete p;
}

void GUI::generateAction(GUI *gui) {
	gui->glwin->reset();
	gui->glwin->update();
}

void GUI::displayMode(GUI *gui, int i) {
}

void GUI::nextSeasonAction(GUI *gui) {
}

QString GUI::randomSeed() {
	return QString::fromStdString(randomString(10));
}

std::string GUI::randomString(int length) {
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
	
	
