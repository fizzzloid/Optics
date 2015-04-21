#include "mainwindow.h"
#include "optics.h"
#include "common_functions.h"
#include <QtWidgets>
#include <QKeyEvent>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	active_field = new field(this);
	setCentralWidget(active_field);

	setMinimumSize(400,400);

	for (int i = -5; i < 6; i++)
	new ray(-0.4, 0.3 + 0.01*i,  0.0, active_field);

	new circle_mirror(vector2D(0.8, 0.2), vector2D(0.8, 0.5),
					  1.0, active_field);

	new sphere(vector2D(0.2, 0.4), 0.1, 1.7, active_field);
	new mirror(vector2D(-0.1, 0.4), vector2D(-0.015, 0.8),
			   true, active_field);
	new thin_lense(vector2D(0.6, 0.4), vector2D(0.65, 0.6),
				   6, active_field);

	active_field->recalc();
	active_field->corner_turn(-0.1, -0.1);
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
	if (active_field->isActiveWindow())
		active_field->keyPressEvent(ke);
}
