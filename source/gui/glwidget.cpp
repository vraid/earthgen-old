#include "glwidget.h"
#include "gui.h"
#include "../planet/planet.h"
#include "../projection/projection.h"
#include "../map/viewport.h"
#include "../math/vector2.h"
#include <vector>
using std::vector;

GLWidget::~GLWidget () {
	delete view;
}

void GLWidget::reset() {
	std::cout << "reset gl\n";
	glLoadIdentity();
}

void GLWidget::initializeGL() {
	if (view == nullptr && width() > 0 && height() > 0) view = new Viewport(width(), height());
	std::cout << "init gl\n";
	glClearColor(0,0,0,0);
	glLoadIdentity();
	scale = 3.0/width();
}

void GLWidget::resizeGL(int w, int h) {
	resizeViewport();
	paintGL();
}

void GLWidget::resizeViewport() {
	if (view == nullptr && width() > 0 && height() > 0) view = new Viewport(width(), height());
	resize_viewport(view, width(), height());
	glViewport(0,0,width(),height());
}

void GLWidget::paintGL() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	double scale = view->scale;
	glOrtho(-width()/scale + view->center.x, width()/scale + view->center.x, -height()/scale + view->center.y, height()/scale + view->center.y, -1.0, 1.0);
	const Planet* p = gui->p;
	const Projection* proj = gui->proj;
	
	for (int i=0; i<mesh::tiles(p); i++) {
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
		const vector<Vector2>& t = proj->north_tile;
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
		if (zoom_time + zoom_focus_reset_delay < time(NULL)) {
			zoom_direction = 0;
		}
		if (event->delta() > 0 && zoom_direction <= 0) {
			zoom_direction = 1;
			zoom_time = time(NULL);
			QPoint p = mapFromGlobal(QCursor::pos());
			double x = 2.0*(p.x() - view->width*0.5);
			double y = -2.0*(p.y() - view->height*0.5);
			zoom_window_focus = Vector2(x, y);
			zoom_map_focus = Vector2(x/view->scale, y/view->scale) + view->center;
		}
		else if (event->delta() < 0 && zoom_direction >= 0) {
			zoom_direction = -1;
			zoom_time = time(NULL);
			QPoint p = mapFromGlobal(QCursor::pos());
			double x = 2.0*(p.x() - view->width*0.5);
			double y = -2.0*(p.y() - view->height*0.5);
			zoom_window_focus = Vector2(x, y);
			zoom_map_focus = Vector2(x/view->scale, y/view->scale) + view->center;
		}
		
		change_scale(view, 1+0.0007*event->delta());
		set_center(view, Vector2(zoom_map_focus.x - zoom_window_focus.x/view->scale, zoom_map_focus.y - zoom_window_focus.y/view->scale));
		updateGL();
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() & Qt::LeftButton) {
	}
}
