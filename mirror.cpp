#include "mirror.h"
#include "field.h"
#include "ray.h"
#include <QtMath>

mirror::mirror(position start, position end, bool orient, field *backg)
	: abstract_optics(backg)
{
	edge_a = start;
	edge_b = end;

	length = edge_a.distance(edge_b);
	tangent.setX(edge_a.x() - edge_b.x());
	tangent.setY(edge_a.y() - edge_b.y());
	tangent /= length;
	normal.setX(tangent.y());
	normal.setY(-tangent.x());
	if (orient) normal *= -1;

	background = backg;
	background->add_optic(this);

	setup_pen_and_bruh();
	generate_outline();

}

mirror::~mirror() {}

position *mirror::intersection_with_ray(ray *r) const
{
	//copypaste from thin_linse
	position e = r->get_emitter_pos();
	position d = r->get_direction_vect();

	qreal Dx = edge_b.x() - edge_a.x();
	qreal Dy = edge_b.y() - edge_a.y();

	qreal denominator = d.x() * Dy - d.y() * Dx;

	if (denominator == 0.0) return 0;	// if ray is parallel to rhe linse

	qreal t = (e.y() - edge_a.y()) * Dx - (e.x() - edge_a.x()) * Dy;
	t /= denominator;

	if (t < 0.00001) return 0; // if ray is starting from the linse
							   // or after linse

	position cross;
	cross.setX(e.x() + d.x() * t);
	cross.setY(e.y() + d.y() * t);

	// if cross is on the same line with the linse,
	// but not between edge_a and edge_b - return 0
	if (Dx != 0.0)
	{
		qreal t1 = ( edge_b.x() - cross.x() ) / Dx;
		if ((t1 < 0.0) || (1.0 < t1)) return 0;
	}
	else if (Dy != 0.0)
	{
		qreal t1 = ( edge_b.y() - cross.y() ) / Dy;
		if ((t1 < 0.0) || (1.0 < t1)) return 0;
	}
	else return 0;

	return new position(cross);
}

ray *mirror::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_brigh) return 0;
	if (r->get_intersection_object() != this) return 0;

	position dir = r->get_direction_vect();
	// if ray is coming from "black" side of mirror
	if (normal.scalar_mult(dir) <= 0) return 0;

	position cross = *r->get_intersection_point();

	position new_dir = dir;

	new_dir -= 2 * normal * normal.scalar_mult(dir);

	ray *new_ray = new ray(cross.x(), cross.y(), new_dir,
						   background,
						   r->get_intensity() - ray::bright_step);
	r->set_child(new_ray);
	generated_rays.append(new_ray);
	return new_ray;
}

void mirror::generate_outline()
{
	outline.moveTo(edge_a);
	outline.lineTo(edge_b);

	position add_vect =  -normal - tangent;
	add_vect /= add_vect.length();
	add_vect *= - length / hatch_count;

	for (quint32 i = 0; i < hatch_count; i++)
	{
		position st_pos(edge_b + i*tangent * length / hatch_count);
		outline.moveTo(st_pos);
		outline.lineTo(st_pos + add_vect);
	}
}
