#ifndef climate_box_h
#define climate_box_h

#include <QGroupBox>
class QPushButton;
class QFormLayout;
class QLineEdit;
class PlanetHandler;
class Climate_parameters;

class ClimateBox : public QGroupBox {
	Q_OBJECT
public:
	ClimateBox (PlanetHandler*);
public slots:
	void generateButtonClicked ();
	void enableButton ();
	void disableButton ();
private:
	void setValues (const Climate_parameters&);

public:
	QFormLayout* form;
	QPushButton* generateButton;
	QLineEdit* seasonsEdit;
	QLineEdit* axialTiltEdit;
	PlanetHandler* planetHandler;
};

#endif