#include "mirror.h"
#include "field.h"
#include "ray.h"
#include "common_functions.h"
#include <QtMath>
#include <QDebug>
mirror::mirror(vector2D start, vector2D end,
			   bool orient, field *backg)
	: abstract_optics(backg)
{
	edge_a = start;
	edge_b = end;

	length = edge_a.distance(edge_b);
	tangent = (edge_a - edge_b) / length;
	normal.setX(-tangent.y());
	normal.setY(tangent.x());
	if (!orient) normal *= -1;

	background = backg;
	background->add_optic(this);

	setup_pen_and_bruh();
	generate_outline();
}

mirror::~mirror() {}

vector2D *mirror::intersection_with_ray(ray *r) const
{
	return common_functions::stretch_intersection(edge_a, edge_b, r);
}

ray *mirror::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;

	vector2D dir = r->get_direction_vect();
	// if ray is coming from "black" side of mirror
	if (normal.scalar_mult(dir) >= 0) return 0;

	vector2D cross = *r->get_intersection_point();

	vector2D new_dir = dir;
	new_dir -= 2 * normal * normal.scalar_mult(dir);

	ray *new_ray = new ray(cross.x(), cross.y(), new_dir,
						   background,
						   r->get_intensity() - ray::intensity_step);
	r->set_child(new_ray);
	return new_ray;
}

void mirror::generate_outline()
{
	outline.moveTo(edge_a);
	outline.lineTo(edge_b);

	vector2D add_vect =  -normal + tangent;
	add_vect /= add_vect.length();
	add_vect *= length / hatch_count;

	for (quint32 i = 0; i < hatch_count; i++)
	{
		vector2D st_pos(edge_b + i*tangent * length / hatch_count);
		outline.moveTo(st_pos);
		outline.lineTo(st_pos + add_vect);
	}
}
