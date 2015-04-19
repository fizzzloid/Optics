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


	new real_lense(vector2D(0.13, 0.2), vector2D(0.15, 0.3),
				   0.1,
				   0.1, -0.1,
				   1.5, mainfield);

	new sphere(vector2D(0.4, 0.25), 0.05, 1.7, mainfield);
	new mirror(vector2D(0.5, 0.1), vector2D(0.7, 0.5),
			   false, mainfield);
	mainfield->recalc();
	mainfield->corner_turn(-0.1, -0.1);
}
