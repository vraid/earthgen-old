#include "glwidget.h"
#include "gui.h"
using std::min;

void GLWidget::reset() {
	glLoadIdentity();
}

void GLWidget::initializeGL() {
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glOrtho(-1.0, 1.0, 1.0, -1.0, -1.0, 1.0);
}

void GLWidget::resizeGL(int width, int height) {
	resizeViewport();
	paintGL();
}

void GLWidget::resizeViewport() {
	int w = 1;
	int h = 1;
	glViewport((GLint)(width()-w)/2, GLint(height()-h)/2, (GLint)(w), (GLint)(h));
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::wheelEvent(QWheelEvent *event) {
	if(event->orientation() == Qt::Vertical) {
		event->delta();
		resizeViewport();
		updateGL();
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() & Qt::LeftButton) {
	}
}
