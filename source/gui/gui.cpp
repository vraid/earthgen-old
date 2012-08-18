#include "gui.h"
#include "glwidget.h"
#include "../planet/planet.h"
#include "../projection/projection.h"

GUI::GUI() {
	p = new Planet();
	par = parameters::load();
	p->par = *par;
	p->mesh = mesh::create(p->par.mesh_size);
	p->terrain = new Terrain();
	terrain::init(p);
	terrain::generate(p);
	
	window = new QWidget();
	window->resize(860,600);
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
