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
}

prism::~prism() {}

position *prism::intersection_with_ray(ray *r) const
{
	qint32 l = polygon.length();
	position e = r->get_emitter_pos();
	qint32 nearest = 0;
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
			nearest = i;
			nearest_intersection = cur_intersect;
		}
	}

	return nearest_intersection;
}

ray *prism::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_brigh) return 0;
	if (r->get_intersection_object() != this) return 0;
	position cross = *r->get_intersection_point();

	qint32 l = polygon.length();
	qreal min_dist = INFINITY;
	qint32 cross_num = 0;
	for (qint32 i = 0; i < l; i++)
	{
		qreal dist = common_functions
				::qist_to_stratch(polygon[i], polygon[(i+1)%l], cross);
		if (dist < min_dist)
		{
			cross_num = i;
			min_dist = dist;
		}
	}

	// todo
}
