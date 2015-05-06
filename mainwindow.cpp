#include "mainwindow.h"
#include "optics.h"
#include "common_functions.h"
#include "ray_options.h"
#include <QtWidgets>
#include <QKeyEvent>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	active_field = new field(this);
	setCentralWidget(active_field);

	setMinimumSize(700,700);
	setup_statusbar();
	connect(active_field, SIGNAL(something_changed()),
			this, SLOT(status_changed()));

	for (int i = -5; i < 6; i++)
	new ray(-0.4, 0.3 + 0.01*i,  0.0, active_field);

	new circle_mirror(vector2D(0.8, 0.2), vector2D(0.8, 0.5),
					  1.0, active_field);

	new sphere(vector2D(0.2, 0.4), 0.1, 1.7, active_field);
	new mirror(vector2D(-0.1, 0.4), vector2D(-0.015, 0.8),
			   true, active_field);
	new thin_lense(vector2D(0.6, 0.4), vector2D(0.65, 0.6),
				   6, active_field);
	new real_lense(vector2D(0.5, 0.4), vector2D(0.55, 0.6),
				   0.01, -0.7, 0.2, 1.7, active_field);

	QPolygonF polygon;
	polygon << common_functions::regular_polygon
			   (vector2D(0.4, 0.0), 0.2, 8) << vector2D(0.4, 0.1);
	new prism(polygon, 1.7, active_field);

	active_field->recalc();
	active_field->corner_turn(-0.1, -0.1);
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
	if (active_field->isActiveWindow())
		active_field->keyPressEvent(ke);
}

void MainWindow::status_changed()
{
	if (active_field)
	{
		QPointF corn = active_field->get_corner();
		QString text("Position: %1, %2; Scale: %3 pixels/meter");
		navigation_label->setText(
									text
									.arg(corn.x())
									.arg(corn.y())
									.arg(active_field->get_scale()
									));
	}
}

void MainWindow::setup_statusbar()
{
	navigation_label = new QLabel
			("Position: 000000, 000000; Scale: 000000 pixels/meter");
	navigation_label->setMinimumSize(navigation_label->sizeHint());
	statusBar()->addWidget(navigation_label);

	status_changed();
}
