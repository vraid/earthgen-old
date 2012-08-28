#include "gui.h"
#include "glwidget.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include <iostream>

GUI::GUI() {
	p = new Planet();
	par = parameters::load();
	p->par = *par;
	p->mesh = mesh::create(p->par.mesh_size);
	p->terrain = new Terrain();
	terrain::init(p);
	terrain::generate(p);

	std::cout << "new projection\n";
	proj = new Projection();
	projection::init(p, proj);
	std::cout << "set colours..";
	projection::set_colors(proj);
	std::cout << " done\n";
	
	window = new QWidget();
	windowLayout = new QHBoxLayout();
		glwin = new GLWidget(window);
		glwin->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
		glwin->gui = this;
		windowLayout->addWidget(glwin);
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
