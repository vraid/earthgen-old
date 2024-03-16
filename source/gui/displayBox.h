#ifndef display_box_h
#define display_box_h

#include <QGroupBox>
class QGridLayout;
class QPushButton;
class QComboBox;
class QLineEdit;

namespace earthgen {

class PlanetHandler;
class PlanetWidget;

class DisplayBox : public QGroupBox {
	Q_OBJECT
public:
	DisplayBox (PlanetHandler*, PlanetWidget*);
public slots:
	void mapButtonClicked ();
	void globeButtonClicked ();
	void colorChanged ();
	void enableTerrain ();
	void enableClimate ();
	void disableClimate ();
	void setSeason (int);
	void incrementSeason ();
	void decrementSeason ();
public:
	QGridLayout* layout;
	QPushButton* mapButton;
	QPushButton* globeButton;
	QComboBox* colorBox;
	QLineEdit* seasonEdit;
	QPushButton* incrementSeasonButton;
	QPushButton* decrementSeasonButton;
	PlanetHandler* planetHandler;
	PlanetWidget* planetWidget;
	bool terrainEnabled;
	bool climateEnabled;
	int currentSeason;
};

}

#endif
