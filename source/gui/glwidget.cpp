#include "glwidget.h"
#include "gui.h"
#include "generationmenu.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include "../map/camera_2d.h"
#include "../math/vector2.h"
#include <cmath>
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
		const vector<Vector2>& t = proj->tile;
		glColor3f(proj->color[3*i], proj->color[3*i+1], proj->color[3*i+2]);
		glBegin(GL_TRIANGLE_FAN);
		for (int k=0; k<7; k++) {
			glVertex2f(t[i*7+k].x, t[i*7+k].y);
		}
		glVertex2f(t[i*7+1].x, t[i*7+1].y);
		glEnd();
	}
	/*
	int id = proj->north_id;
	if (id >= 0) {
		const vector<Vector2>& t = proj->north_tile;std::precision(2)
		glColor3f(proj->color[3*id], proj->color[3*id+1], proj->color[3*id+2]);
		glBegin(GL_TRIANGLE_FAN);
		for (unsigned int i=0; i<proj->north_tile.size(); i++) {
			glVertex2f(t[i].x, t[i].y);
		}
		glVertex2f(t[1].x, t[1].y);
		glEnd();
	}
	id = proj->south_id;
	if (id >= 0) {
		const vector<Vector2>& t = proj->south_tile;
		glColor3f(proj->color[3*id], proj->color[3*id+1], proj->color[3*id+2]);
		glBegin(GL_TRIANGLE_FAN);
		for (unsigned int i=0; i<proj->south_tile.size(); i++) {
			glVertex2f(t[i].x, t[i].y);
		}
		glVertex2f(t[1].x, t[1].y);
		glEnd();
	}
	*/
}

void GLWidget::wheelEvent(QWheelEvent *event) {
	if(event->orientation() == Qt::Vertical) {
		if (zoomTime + zoomFocusResetDelay < time(NULL)) {
			resetZoom();
		}
		if (event->delta() > 0 && zoomDirection <= 0) {
			zoomDirection = 1;
			zoomTime = time(NULL);
			captureMousePosition();
		}
		else if (event->delta() < 0 && zoomDirection >= 0) {
			zoomDirection = -1;
			zoomTime = time(NULL);
			captureMousePosition();
		}
		
		change_scale(camera, 1+zoomSpeed*event->delta());
		set_position(camera, mouseMapPosition - mouseWindowPosition/camera->scale);
		updateGL();
	}
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
			// coordinateSelectionLabel->setText(QString::fromStdString(s));
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
