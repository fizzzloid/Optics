#include "prism.h"
#include "field.h"
#include "ray.h"
#include "common_functions.h"
#include <QtMath>

prism::prism(QPolygonF p, qreal index_of_refraction, field *backg)
	: abstract_optics(backg)
{
	polygon = p;
	index_of_refr = index_of_refraction;
	calculate_geometry();
	setup_pen_and_bruh();
	generate_outline();
}

prism::~prism() {}

position *prism::intersection_with_ray(ray *r) const
{
	qint32 l = polygon.length();
	position e = r->get_emitter_pos();
	position *nearest_intersection = 0;
	qreal nearest_dist = INFINITY;
	for(qint32 i = 0; i < l; i++)
	{
		position p1 = polygon[i];
		position p2 = polygon[(i+1)%l];
		position *cur_intersect =
			common_functions::stretch_intersection(p1, p2, r);
		if (cur_intersect && (e.distance(*cur_intersect) < nearest_dist))
		{
			nearest_dist = e.distance(*cur_intersect);
			nearest_intersection = cur_intersect;
		}
	}

	return nearest_intersection;
}

ray *prism::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;
	position cross = *r->get_intersection_point();

	qint32 l = polygon.length();
	qreal min_dist = INFINITY;
	qint32 cross_num = 0;
	for (qint32 i = 0; i < l; i++)
	{
		qreal dist = common_functions
				::dist_to_stratch(polygon[i], polygon[(i+1)%l], cross);
		if (dist < min_dist)
		{
			cross_num = i;
			min_dist = dist;
		}
	}

	// sin(alpha)/sin(betta) = n1 / n2
	position n(normal[cross_num]);
	position d(r->get_direction_vect());

	qreal tetta;
	qreal cos_alpha = n.scalar_mult(d);
	qreal sin_alpha = n.vect_mult(d);
	if (cos_alpha > 0)
		tetta = index_of_refr / background->get_index_of_refraction();
	else tetta = background->get_index_of_refraction() / index_of_refr;
	qreal sin_betta = -sin_alpha * tetta;

	position dir;
	if (qFabs(sin_betta) > 1.0) //total inside refraction
		dir = d - 2 * n*n.scalar_mult(d);
	else
	{
		qreal cos_betta = qSqrt(1 - sin_betta * sin_betta);
		if (cos_alpha < 0) cos_betta *= -1;
		dir = tangent[cross_num] * sin_betta + n * cos_betta;
	}
	ray *new_ray = new ray(cross.x(), cross.y(), dir, background,
				   r->get_intensity() - ray::intensity_step);
	r->set_child(new_ray);
	return new_ray;
}

void prism::calculate_geometry()
{
	qint32 l = polygon.length();

	position e1 = (polygon[0] + polygon[1%l]) / 2;
	position n1;
	position t(polygon[1%l] - polygon[0]);
	t /= t.length();
	n1.setX(-t.y());
	n1.setY(t.x());

	qint32 count = 0;
	ray *trial_ray =
			new ray(e1.x(), e1.y(), n1, background);

	for (qint32 i = 0; i < l; i++)
	{
		position p1 = polygon[i];
		position p2 = polygon[(i+1)%l];
		tangent.append( (p2 - p1) / p1.distance(p2) );

		if (common_functions::stretch_intersection(p1, p2, trial_ray))
			count++;
	}

	background->delete_ray(trial_ray);
	delete trial_ray;

	qint32 sign;
	if (count%2) sign = -1;
	else sign = 1;

	for (qint32 i = 0; i < l; i++)
	{
		position n(-tangent[i].y(), tangent[i].x());
		normal.append(n*sign);
	}
}

void prism::generate_outline()
{
	outline.moveTo(polygon[0]);
	qint32 l = polygon.length();
	for (qint32 i = 0; i < l; i++)
		outline.lineTo(polygon[i]);
	outline.lineTo(polygon[0]);
}
