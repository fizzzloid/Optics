#include "mainwindow.h"
#include "optics.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainfield = new field(this);
	setCentralWidget(mainfield);

	new ray(50.0, 100.0, 0.0, mainfield);
	new thin_linse(position(80.0, 50.0), position(80.0, 120.0), 1.0, mainfield);
}
