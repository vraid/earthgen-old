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

	void reset_zoom();
	void capture_mouse_position();

//	void keyPressEvent( QKeyEvent *e ) {};
public:
	GUI* gui;
	double scale;
	Viewport* view;
	Vector2 mouse_map_position;
	Vector2 mouse_window_position;
	int zoom_direction;
	time_t zoom_time;
	time_t zoom_focus_reset_delay;
};

#endif
