#include "mainwindow.h"
#include "optics.h"
#include "retroplane.h"
#include "common_functions.h"
#include "ray_options.h"
#include <QtWidgets>
#include <QKeyEvent>
#include <QtMath>
//#include <boost/range/adaptor/indexed.hpp>

//using namespace boost::adaptors;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	active_field = new field(this);

    setCentralWidget(active_field);

	setMinimumSize(700,700);

    setup_statusbar();

    connect(active_field, SIGNAL(something_changed()),
			this, SLOT(status_changed()));

    auto fr = [&](int i)
    {
        new ray(100.0, 350 + 10*i,  vector2D(1, 0), active_field);
        //new ray(0.4, 0.285 + 0.01*i,  0.0, active_field);
    };

    // array of beams
    for(int i = 0; i<5; ++i)
    {
        fr(-8 + i);
    }

    new real_lense(vector2D(200, 400), vector2D(200, 200),
                   10.0, 50.0, 50.0, 1.5, active_field);
    new mirror(vector2D(450.0, 400), vector2D(450.0, 200.0),
               true, active_field);

	active_field->recalc();

    active_field->corner_turn(0.0, 0.0);
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
    navigation_label = new QLabel(
    "Position: 000000, 000000; Scale: 000000 pixels/meter"
                );

    navigation_label->setMinimumSize(navigation_label->sizeHint());

    statusBar()->addWidget(navigation_label);

	status_changed();
}
