#ifndef gui_h
#define gui_h


#include <iostream>
#include <string>
#include <QString>

class QWidget;
class QLayout;
class QGridLayout;
class QFormLayout;
class QLabel;
class QCheckBox;
class QPushButton;
class QLineEdit;
class QIntValidator;

class GLWidget;
class Planet;
class Parameters;
class Projection;

class GUI {
public:
	GUI();
	~GUI();
private:
	static void generateAction (GUI*);
	static void displayMode (GUI*,int);
	static void nextSeasonAction (GUI*);
	static QString randomSeed ();
	static std::string randomString (int);
public:
	QWidget* window;
	QGridLayout* windowLayout;
	QWidget* sideMenu;
	QFormLayout* sideMenuLayout;
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
	GLWidget* glwin;

	Planet* p;
	Parameters* par;
	Projection* proj;
};

#endif
