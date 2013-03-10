#ifndef planet_widget_h
#define planet_widget_h

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "../math/vector2.h"
#include "../math/vector3.h"
class PlanetHandler;
class Planet_renderer;
class Globe_renderer;
class Map_renderer;
class Empty_renderer;
class Planet_colours;

class PlanetWidget : public QGLWidget {
	Q_OBJECT
public:
	PlanetWidget (PlanetHandler*);
protected:
	void initializeGL ();
	void resizeGL (int, int);
	void resizeViewport ();
	void paintGL ();
	void wheelEvent (QWheelEvent*);
	void mousePressEvent (QMouseEvent*);
	void mouseReleaseEvent (QMouseEvent*);
	void mouseMoveEvent (QMouseEvent*);
	void getMousePosition ();
private:
	Vector2 relativePosition (const QPointF&);
	Vector2 vector (const QPoint&) const;
public slots:
	void update ();
	void activateGlobeRenderer ();
	void activateMapRenderer ();
	void updateGeometry ();
	void initColours ();
signals:
	void pointSelected (Vector3);
public:
	bool mouseMoving;
	QPoint mousePosition;
	PlanetHandler* planetHandler;
	Planet_renderer* activeRenderer;
	Globe_renderer* globeRenderer;
	Map_renderer* mapRenderer;
	Empty_renderer* emptyRenderer;
	Planet_colours* colours;
};

#endif