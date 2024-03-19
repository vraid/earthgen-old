#include "planetWidget.h"
#include "planetHandler.h"
#include "../render/empty_renderer.h"
#include "../render/globe_renderer.h"
#include "../render/map_renderer.h"
#include "../render/planet_colors.h"
#include "../../math/quaternion.h"

namespace earthgen {

PlanetWidget::PlanetWidget (PlanetHandler* p) : planetHandler(p) {
	emptyRenderer = new Empty_renderer();
	globeRenderer = new Globe_renderer();
	mapRenderer = new Map_renderer();
	activeRenderer = emptyRenderer;
	colors = new Planet_colors();
	mouseMoving = false;
	
	QObject::connect(planetHandler, SIGNAL(terrainCreated()), this, SLOT(initColors()));
	QObject::connect(planetHandler, SIGNAL(terrainCreated()), this, SLOT(updateGeometry()));
	QObject::connect(planetHandler, SIGNAL(axisChanged()), this, SLOT(updateGeometry()));
}

void PlanetWidget::update () {
	updateGL();
}

void PlanetWidget::initializeGL () {
	glClearColor(0,0,0,0);
	glLoadIdentity();
}

void PlanetWidget::resizeGL (int, int) {
	resizeViewport();
	paintGL();
}
void PlanetWidget::resizeViewport () {
	glViewport(0, 0, width(), height());
	activeRenderer->set_viewport_size(width(), height());
}

void PlanetWidget::paintGL () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);
	if (width() && height()) {
		activeRenderer->draw(planetHandler->grid(), rotation_to_default(planetHandler->terrain()), *colors);
	}
}

void PlanetWidget::wheelEvent (QWheelEvent* event) {
	getMousePosition();
	int dy = event->angleDelta().y();
	if(dy) {
		activeRenderer->change_scale(vector(mousePosition), 1+0.0007*dy);
		update();
	}
}

void PlanetWidget::mousePressEvent (QMouseEvent*) {
	getMousePosition();
//	QPoint p = QPoint(1,2) - QPoint(10,10);
}

void PlanetWidget::mouseReleaseEvent (QMouseEvent*) {
	if (!mouseMoving) {
		pointSelected(conjugate(rotation_to_default(planetHandler->terrain())) * activeRenderer->to_coordinates(vector(mousePosition)));
	}
	mouseMoving = false;
}

void PlanetWidget::mouseMoveEvent (QMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		QPoint newMousePosition = mapFromGlobal(QCursor::pos());
		Vector2 delta = vector(newMousePosition - mousePosition);
		activeRenderer->mouse_dragged(delta);
		update();
		mouseMoving = true;
		mousePosition = newMousePosition;
	}
}

Vector2 PlanetWidget::relativePosition (const QPointF& p) {
	return Vector2(p.x() - 0.5*width(), 0.5*height() - p.y());
}

void PlanetWidget::getMousePosition () {
	mousePosition = mapFromGlobal(QCursor::pos());
}

Vector2 PlanetWidget::vector (const QPoint& p) const {
	return Vector2(p.x(), p.y());
}

void PlanetWidget::activateGlobeRenderer () {
	globeRenderer->set_viewport_size(width(), height());
	activeRenderer = globeRenderer;
}

void PlanetWidget::activateMapRenderer () {
	mapRenderer->set_viewport_size(width(), height());
	activeRenderer = mapRenderer;
}

void PlanetWidget::updateGeometry () {
	mapRenderer->update_geometry();
	update();
}

void PlanetWidget::initColors () {
	init_colors(*colors, planetHandler->grid());
	set_colors(*colors, planetHandler->grid(), planetHandler->terrain(), planetHandler->currentSeason(), 0);
}

}
