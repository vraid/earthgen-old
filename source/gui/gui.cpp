#include "gui.h"
#include "generationmenu.h"
#include "glwidget.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include <iostream>
#include <QObject>
#include <QWidget>
#include <QLayout>

GUI::GUI() {
	p = nullptr;
	proj = nullptr;
	glwin = nullptr;
	loadParameters();
	resetPlanet();

//	generateTerrain();

	window = new QWidget();
	windowLayout = new QGridLayout();
		sideMenu = new GenerationMenu(this);
		windowLayout->addWidget(sideMenu, 0, 0, 2, 1, 0);
		sideMenu->generateTerrain();
		
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

void GUI::loadParameters() {
	par = parameters::load();
}

void GUI::resetPlanet() {
	delete p;
	p = new Planet();
	p->par = *par;
	delete proj;
	proj = new Projection();
}

void GUI::generateTerrain() {
	p->grid = grid::create(p->par.grid_size);
	terrain::generate(p);
	
	projection::init(p, proj);
	projection::set_colors(proj);
	projection::color_topography(proj);
	if (glwin) glwin->update();
}

void GUI::generateClimate() {
}
