#ifndef axis_box_h
#define axis_box_h

#include <QGroupBox>
#include "../math/vector3.h"
class QFormLayout;
class QLineEdit;
class QPushButton;
class PlanetHandler;
class PlanetWidget;

class AxisBox : public QGroupBox {
	Q_OBJECT
public:
	AxisBox (PlanetHandler*, PlanetWidget*);
public slots:
	void setSelection (const Vector3&);
	void enableButton ();
	void setButtonClicked ();
	void setAxis ();

public:
	QFormLayout* form;
	QPushButton* setButton;
	QLineEdit* axisEdit;
	QLineEdit* selectedEdit;
	Vector3 selected;
	PlanetHandler* planetHandler;
};

#endif