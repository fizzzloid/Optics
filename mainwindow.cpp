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
	new ray(0.00, 0.25 + 0.01*i,  0.0, mainfield);

	new circle_mirror(vector2D(0.4, 0.2), vector2D(0.5, 0.5),
					  -0.3, mainfield);

	mainfield->recalc();
	mainfield->corner_turn(-0.1, -0.1);
}
