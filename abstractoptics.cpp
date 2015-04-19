#include "abstractoptics.h"
#include "vector2D.h"
#include "ray.h"
#include "field.h"
#include <QPainterPath>
#include <QPair>

abstract_optics::abstract_optics(field *backg)
{
	background = backg;
	background->add_optic(this);
	setup_pen_and_brush();
}

abstract_optics::~abstract_optics() {}

QPair<vector2D *, qint32> abstract_optics::intersection_with_ray(ray *) const
{
	return QPair<vector2D *, qint32>(0,0);
}

ray *abstract_optics::generate_ray(ray *)
{
	return 0;
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

void abstract_optics::setup_pen_and_brush()
{
	pen.setColor(Qt::blue);
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);

	QColor brush_color(Qt::darkBlue);
	brush_color.setAlphaF(0.3);
	brush.setColor(brush_color);
	brush.setStyle(Qt::SolidPattern);
}

void abstract_optics::generate_outline() {}
