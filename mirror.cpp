#include "mirror.h"
#include "field.h"
#include "ray.h"
#include "common_functions.h"
#include <QtMath>
#include <QDebug>
#include <QPair>
#include <QString>

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

	setup_pen_and_brush();
	generate_outline();
}

mirror::~mirror() {}

QPair<vector2D *, qint32> mirror::intersection_with_ray(ray *r) const
{
	vector2D *v = common_functions::stretch_intersection(edge_a, edge_b, r);
	return QPair<vector2D *, qint32> (v, 0);
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

qreal mirror::get_distance_to_point(vector2D p) const
{ return common_functions::dist_to_stratch(edge_a, edge_b, p); }

QString mirror::who_i_am() const { return QString("Mirror"); }

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
