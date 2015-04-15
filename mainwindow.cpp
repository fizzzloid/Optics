#include "mainwindow.h"
#include "optics.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainfield = new field(this);
	setCentralWidget(mainfield);

	setMinimumSize(400,200);

	qreal angle = 0.2;
	new ray(0.05, 0.060, angle, mainfield);
	new ray(0.05, 0.085, angle, mainfield);
	new ray(0.05, 0.100, angle, mainfield);
	new ray(0.04, 0.060, -angle, mainfield);
	new ray(0.04, 0.085, -angle, mainfield);
	new ray(0.04, 0.100, -angle, mainfield);
	for (qreal x = 0.06; x < 1.0; x += 0.05)
	 new thin_linse(position(x, 0.05), position(x, 0.12), 10.0, mainfield);
	mainfield->recalc();
}
