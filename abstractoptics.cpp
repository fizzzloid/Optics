#include "abstractoptics.h"
#include "position.h"
#include "ray.h"
#include "field.h"
#include <QPainterPath>
#include <QDebug>
abstract_optics::abstract_optics(field *backg)
{
	background = backg;
	background->add_optic(this);
	setup_pen_and_bruh();
}

abstract_optics::~abstract_optics() {}

position *abstract_optics::intersection_with_ray(ray *) const
{
	qDebug() << "abstract";
	return 0;
}

ray *abstract_optics::generate_ray(ray *)
{
	return 0;
}

QList<ray *> abstract_optics::get_generated_rays() const
{
	return generated_rays;
}

void abstract_optics::delete_ray(ray *r)
{
	generated_rays.removeOne(r);
}

QPainterPath abstract_optics::get_outline() const
{
	return outline;
}

QBrush abstract_optics::get_brush() const
{
	return brush;
}

QPen abstract_optics::get_pen() const
{
	return pen;
}

void abstract_optics::setup_pen_and_bruh() {}

void abstract_optics::generate_outline() {}
