#include "mainwindow.h"
#include "optics.h"
#include "common_functions.h"
#include <QtWidgets>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	active_field = new field(this);
	setCentralWidget(active_field);

	setMinimumSize(400,400);

	for (int i = -3; i < 4; i++)
	new ray(0.00, 0.25 + 0.01*i,  0.0, active_field);

	new circle_mirror(vector2D(0.8, 0.2), vector2D(0.8, 0.5),
					  1.3, active_field);

	active_field->recalc();
	active_field->corner_turn(-0.1, -0.1);
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
	if (active_field->isActiveWindow())
		active_field->keyPressEvent(ke);
}
