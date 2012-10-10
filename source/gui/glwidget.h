#ifndef glwidget_h
#define glwidget_h
 
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "../math/vector2.h"
#include <ctime>
class GUI;
class Viewport;

#define nullptr NULL

class GLWidget : public QGLWidget {
public:
	GLWidget(QWidget *parent) : QGLWidget(parent) {
		view = nullptr;
		zoom_time = 0;
		zoom_focus_reset_delay = 1.0;
		zoom_direction = 0;
	}
	~GLWidget();
	void reset();
protected:
	void initializeGL();
	void resizeGL(int,int);
	void resizeViewport();
	void paintGL();
	void wheelEvent(QWheelEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);

//	void keyPressEvent( QKeyEvent *e ) {};
public:
	GUI* gui;
	double scale;
	Viewport* view;
	int zoom_direction;
	Vector2 zoom_map_focus;
	Vector2 zoom_window_focus;
	time_t zoom_time;
	time_t zoom_focus_reset_delay;
};

#endif
