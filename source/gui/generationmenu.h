#ifndef generationmenu_h
#define generationmenu_h

#include <QWidget>
#include "../math/vector3.h"
#include "../math/quaternion.h"

class GUI;
class QDoubleValidator;
class QFormLayout;
class QIntValidator;
class QLabel;
class QLineEdit;
class QPushButton;

class GenerationMenu : public QWidget {
	Q_OBJECT
public:
	GenerationMenu (GUI*);
	~GenerationMenu() {};
private:
	static std::string randomString (int);
	static QString randomSeed ();
	static QString vectorToString(Vector3);
public slots:
	void generateTerrain();
	void generateClimate();
	void resetAxis();
	void setAxis();
	void setSelectedCoordinate(Vector3);
	void updateTerrainParameters();
	void updateClimateParameters();
private:
	QFormLayout* layout;
	QPushButton* generateTerrainButton;
	QLineEdit* seedEdit;
	QLineEdit* iterationEdit;
	QIntValidator* iterationValidator;
	QLineEdit* gridSizeEdit;
	QIntValidator* gridSizeValidator;
	QLineEdit* waterRatioEdit;
	QDoubleValidator* waterRatioValidator;
	QPushButton* setAxisButton;
	QLabel* axisLabel;
	QLabel* coordinateSelectionLabel;
	QPushButton* generateClimateButton;
	QLineEdit* seasonsEdit;
	QIntValidator* seasonsValidator;

	GUI* gui;
	Vector3 axis;
	Vector3 selectedCoordinate;
	Quaternion oldRotation;
	std::string oldSeed;
};

#endif
