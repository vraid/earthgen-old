#include <iostream>
#include <QtCore>
#include <QApplication>

#include "source/gui/gui.h"


int main(int argv, char **args) {
	QApplication app(argv, args);
	GUI* mainGUI = new GUI();
	return app.exec();
}
