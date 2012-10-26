#include "glwidget.h"
#include "gui.h"
#include "generationmenu.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include "../map/camera_2d.h"
#include "../math/vector2.h"
#include <cmath>
#include <iomanip>
#include <vector>
using std::vector;

GLWidget::~GLWidget () {
	delete camera;
}

void GLWidget::reset() {
	glLoadIdentity();
}

void GLWidget::initializeGL() {
	if (camera == nullptr && width() > 0 && height() > 0) camera = new Camera_2d(width(), height());
	glClearColor(0,0,0,0);
	glLoadIdentity();
}

void GLWidget::resizeGL(int w, int h) {
	resizeViewport();
	paintGL();
}

void GLWidget::resizeViewport() {
	if (camera == nullptr && width() > 0 && height() > 0) camera = new Camera_2d(width(), height());
	resize_camera(camera, width(), height());
	glViewport(0,0,width(),height());
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double scale = camera->scale;
	glLoadIdentity();
	glOrtho(-width()/scale + camera->position.x, width()/scale + camera->position.x, -height()/scale + camera->position.y, height()/scale + camera->position.y, -1.0, 1.0);
	const Planet* p = gui->p;
	const Projection* proj = gui->proj;
	
	for (int i=0; i<grid::tiles(p); i++) {
		glColor3f(proj->color[3*i], proj->color[3*i+1], proj->color[3*i+2]);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(proj->tile_center[i].x, proj->tile_center[i].y);
		for (int k=0; k<6; k++) {
			glVertex2f(proj->tile_corner[i*6+k].x, proj->tile_corner[i*6+k].y);
		}
		glVertex2f(proj->tile_corner[i*6].x, proj->tile_corner[i*6].y);
		glEnd();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
	if(event->orientation() == Qt::Vertical) {
		if (event->delta() > 0) {
			zoomDirection = 1;
		}
		else if (event->delta() < 0) {
			zoomDirection = -1;
		}
		captureMousePosition();
		change_scale(camera, 1+zoomSpeed*event->delta());
		set_position(camera, mouseMapPosition - mouseWindowPosition/camera->scale);
		updateGL();
	}
	resetZoom();
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
	resetZoom();
	captureMousePosition();
	mouseMoving = false;
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (mouseMoving == false) {
		if (pow(mouseMapPosition.x/sqrt(8.0),2.0) + pow(mouseMapPosition.y/sqrt(2.0),2.0) <= 1) {
			Vector3 v = projection::from_hammer(mouseMapPosition);
			gui->sideMenu->setSelectedCoordinate(v);
		}
	}
	mouseMoving = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
	mouseMoving = true;
	if (event->buttons()) resetZoom();
	if (event->buttons() & Qt::LeftButton) {
		QPoint p = mapFromGlobal(QCursor::pos());
		double x = 2.0*(p.x() - camera->width*0.5);
		double y = -2.0*(p.y() - camera->height*0.5);
		mouseWindowPosition = Vector2(x, y);
		set_position(camera, mouseMapPosition - mouseWindowPosition/camera->scale);
		updateGL();
	}
}

void GLWidget::resetZoom() {
	zoomDirection = 0;
}

void GLWidget::captureMousePosition() {
	QPoint p = mapFromGlobal(QCursor::pos());
	double x = 2.0*(p.x() - camera->width*0.5);
	double y = -2.0*(p.y() - camera->height*0.5);
	mouseWindowPosition = Vector2(x, y);
	mouseMapPosition = Vector2(x/camera->scale, y/camera->scale) + camera->position;
}
