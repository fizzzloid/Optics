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

	//for (int i = -3; i < 4; i++)
	new ray(0.45, 0.25, M_PI + 0.2, mainfield);

	new real_lense(vector2D(0.15, 0.05), vector2D(0.15, 0.45),
				   0.1,
				   0.0, -0.1, 1.5, mainfield);

//	new sphere(vector2D(0.3, 0.15), 0.1, 1.5, mainfield);

	mainfield->recalc();
	mainfield->corner_turn(-0.1, -0.1);
}
