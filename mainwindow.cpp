#include "mainwindow.h"
#include "optics.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainfield = new field(this);
	setCentralWidget(mainfield);

	setMinimumSize(400,200);

	new ray(0.30, 0.05, 0.002, mainfield);
	new mirror(position(0.50, 0.05), position(0.50, 0.15),
			   true, mainfield);
	new mirror(position(0.10, 0.05), position(0.10, 0.15),
			   false, mainfield);


	mainfield->recalc();
}
