#include "mainwindow.h"
#include "optics.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainfield = new field(this);
	setCentralWidget(mainfield);

	setMinimumSize(400,200);

	new ray(0.60, 0.05, 3.1415, mainfield);
	new thin_linse(position(0.3, 0.01), position(0.3, 0.20), 10, mainfield);
	new mirror(position(0.05, 0.05), position(0.05, 0.25), false, mainfield);
	new mirror(position(0.05, 0.25), position(0.25, 0.25), false, mainfield);
	mainfield->recalc();
}
