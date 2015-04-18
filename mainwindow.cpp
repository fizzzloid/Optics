#include "mainwindow.h"
#include "optics.h"
#include <QtWidgets>
#include "common_functions.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainfield = new field(this);
	setCentralWidget(mainfield);

	setMinimumSize(700,700);

	for (int i = -3; i < 4; i++)
	new ray(0.50, 0.15, M_PI + i*0.13, mainfield);

	new sphere(QPointF(0.35, 0.15), 0.06, 1.5, mainfield);

	mainfield->recalc();
	mainfield->corner_turn(-0.1, -0.1);
}
