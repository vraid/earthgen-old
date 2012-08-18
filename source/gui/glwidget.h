#ifndef glwidget_h
#define glwidget_h
 
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>

class GLWidget : public QGLWidget {
public:
	GLWidget(QWidget *parent) : QGLWidget(parent) {};
	~GLWidget() {};
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
};

#endif
