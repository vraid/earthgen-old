#ifndef generationmenu_h
#define generationmenu_h

#include <QWidget>
#include "../math/vector3.h"

class GUI;
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
public slots:
	void generate();
	void setAxis();
	void setSelectedCoordinate(Vector3);
	void updateParameters();
private:
	QFormLayout* layout;
	QPushButton* generateButton;
	QLineEdit* seedEdit;
	QLineEdit* iterationEdit;
	QIntValidator* iterationValidator;
	QLineEdit* gridSizeEdit;
	QIntValidator* gridSizeValidator;
	QLabel* axisLabel;
	QLabel* coordinateSelectionLabel;
	QPushButton* setAxisButton;
	QLineEdit* seasonsEdit;
	QIntValidator* seasonsValidator;

	GUI* gui;
	Vector3 selectedCoordinate;
};

#endif
