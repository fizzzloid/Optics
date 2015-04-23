#include "obj_selection_menu.h"
#include <QAction>
#include <QSet>

obj_selection_menu::obj_selection_menu(QSet<qint32> hl_rays,
									   QSet<qint32> hl_optics,
									   QWidget *parent) : QMenu(parent)
{
	bool f1 = hl_rays.count() > 0;
	if (f1)
	{
		QAction *title_rays = new QAction("Rays:", this);
		title_rays->setEnabled(false);
		addAction(title_rays);
		foreach (qint32 n, hl_rays)
		{
			QAction *a = new QAction(QString("Ray #%2").arg(n),
									 this);
			a->setData(n);
			connect(a, SIGNAL(triggered()),
					this, SLOT(click_ray()));
			connect(a, SIGNAL(hovered()),
					this, SLOT(on_ray()));
			addAction(a);
		}
	}

	bool f2 = hl_optics.count() > 0;
	if (f2)
	{
		QAction *title_optics = new QAction("Opcits:", this);
		title_optics->setEnabled(false);
		addAction(title_optics);
		foreach (qint32 n, hl_optics)
		{
			QAction *a = new QAction(QString("Optic #%2")
									 .arg(n), this);
			a->setData(n);
			connect(a, SIGNAL(triggered()),
					this, SLOT(click_optic()));
			connect(a, SIGNAL(hovered()),
					this, SLOT(on_optic()));
			addAction(a);
		}
	}
}

obj_selection_menu::~obj_selection_menu() {}

void obj_selection_menu::on_ray()
{
	QAction *a = (QAction *) sender();
	emit mouse_on_ray(a->data().toInt());
}

void obj_selection_menu::on_optic()
{
	QAction *a = (QAction *) sender();
	emit mouse_on_optic(a->data().toInt());
}

void obj_selection_menu::click_ray()
{
	QAction *a = (QAction *) sender();
	emit ray_selected(a->data().toInt());
	close();
}

void obj_selection_menu::click_optic()
{
	QAction *a = (QAction *) sender();
	emit optic_selected(a->data().toInt());
	close();
}
