#include "thin_linse.h"
#include "ray.h"
#include <QtMath>
#include <QPainter>
#include <QPen>

thin_linse::thin_linse(position start, position end,
					   qreal dioptr, field *backg) : abstract_optics(backg)
{
	edge_a.setX(start.x());
	edge_a.setY(start.y());
	edge_b.setX(end.x());
	edge_b.setY(end.y());

	center.setX(edge_a.x() + edge_b.x());
	center.setY(edge_a.y() + edge_b.y());
	center /= 2.0;
	radius = edge_a.distance(edge_b) / 2.0;

	position t(edge_a);
	t -= edge_b;
	t /= 2 * radius;

	normal.setX(-t.y());
	normal.setY(t.x());
	angle = qAcos(normal.x() / normal.length());

	D = dioptr;

	generate_outline();
}

thin_linse::thin_linse(position cntr, position norm, qreal r,
					   qreal dioptr, field *backg) : abstract_optics(backg)
{
	center.setX(cntr.x());
	center.setY(cntr.y());
	normal.setX(norm.x());
	normal.setY(norm.y());
	normal /= normal.length();

	radius = r;
	D = dioptr;

	edge_a.setX(center.x() - normal.y()*r);
	edge_a.setY(center.y() + normal.x()*r);
	edge_b.setX(center.x() + normal.y()*r);
	edge_b.setY(center.y() - normal.x()*r);

	angle = qAcos(normal.x() / normal.length());

	generate_outline();
}

thin_linse::~thin_linse() {}

position *thin_linse::intersection_with_ray(ray *r) const
{
	position emitter = r->get_emitter_pos();
	position direction = r->get_direction_vect();

	qreal Dx = edge_b.x() - edge_a.x();
	qreal Dy = edge_b.y() - edge_a.y();

	bool a, b;
	if ( (a = (Dx == 0.0)) && (emitter.x() != edge_a.x()) ) return 0;
	if ( (b = (Dy == 0.0)) && (emitter.y() != edge_a.y()) ) return 0;
	if ( a && b ) return 0;
	if ( direction.x() * Dy == direction.y() * Dx ) return 0;

	position cross(direction);
	qreal t = ( (emitter.y() - edge_a.y()) / Dy - (emitter.x() - edge_a.x()) / Dx ) /
			(direction.x() / Dx - direction.y() / Dy);

	if (t > 0) cross *= t;
	else return 0;

	cross += emitter;

	if (edge_a.x() < edge_b.x())
		if ( (cross.x() < edge_a.x()) || (cross.x() > edge_b.x()) ) return 0;
		else return new position(cross);
	else if ( (cross.x() > edge_a.x()) || (cross.x() < edge_b.x()) ) return 0;
		else return new position(cross);
}

ray *thin_linse::generate_ray(ray *r)
{
	if (r->get_intersection_object() != this) return 0;
	position cross = *r->get_intersection_point();

	qreal R = center.distance(cross);
	if (cross.distance(edge_a) > cross.distance(edge_b)) R *= -1;

	// tg arccos |(normal, r->dir_vector)|
	position v( r->get_direction_vect() );
	qreal scalar = normal.scalar_mult(v);
	qreal long_equation = qTan(qAcos(qFabs(scalar)));

	qreal b = qAtan( R*D - long_equation);

	ray *new_ray = new ray(cross.x(), cross.y(), b + angle, background);
	new_ray->set_parent(r);
	generated_rays.append(new_ray);
	return new_ray;
}

void thin_linse::setup_pen_and_bruh()
{
	pen.setColor(Qt::black);
	pen.setWidth(4);
	pen.setStyle(Qt::SolidLine);

	QColor brush_color(Qt::blue);
	brush_color.setAlphaF(0.7);
	brush.setColor(brush_color);
	brush.setStyle(Qt::SolidPattern);
}

void thin_linse::generate_outline()
{
	outline.moveTo(edge_a);
	outline.lineTo(edge_b);
}
