#ifndef glwidget_h
#define glwidget_h
 
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "../math/vector2.h"
#include <ctime>
class GUI;
class Camera_2d;

#define nullptr NULL

class GLWidget : public QGLWidget {
public:
	GLWidget(QWidget *parent) : QGLWidget(parent) {
		camera = nullptr;
		zoomDirection = 0;
		zoomSpeed = 0.0007;
	}
	~GLWidget();
	void reset();
protected:
	void initializeGL();
	void resizeGL(int,int);
	void resizeViewport();
	void paintGL();
	void paintRivers();
	void paintWind();
	void wheelEvent(QWheelEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);

	void resetZoom();
	void captureMousePosition();

//	void keyPressEvent( QKeyEvent *e ) {};
public:
	GUI* gui;
	Camera_2d* camera;
	bool mouseMoving;
	Vector2 mouseMapPosition;
	Vector2 mouseWindowPosition;
	int zoomDirection;
	double zoomSpeed;
};

#endif
