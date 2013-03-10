#ifndef terrain_box_h
#define terrain_box_h

#include <QGroupBox>
#include "../math/vector3.h"

class QFormLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class PlanetHandler;
class Terrain_parameters;

class TerrainBox : public QGroupBox {
	Q_OBJECT
public:
	TerrainBox (PlanetHandler*);
public slots:
	void generateButtonClicked ();
private:
	bool noSeed ();
	void setValues (const Terrain_parameters&);

public:
	QPushButton* generateButton;
	QFormLayout* form;
	QLineEdit* gridSizeEdit;
	QLineEdit* seedEdit;
	QLineEdit* iterationsEdit;
	QLineEdit* waterRatioEdit;
	PlanetHandler* planetHandler;
};

#endif