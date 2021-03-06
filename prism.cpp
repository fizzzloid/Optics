#include "prism.h"
#include "field.h"
#include "ray.h"
#include "common_functions.h"
#include <QtMath>
#include <QPair>
#include <QDebug>
prism::prism(QPolygonF p, qreal index_of_refraction, field *backg)
	: abstract_optics(backg)
{
	polygon = p;
	index_of_refr = index_of_refraction;
	calculate_geometry();
	setup_pen_and_brush();
	generate_outline();
}

prism::~prism() {}

QPair<vector2D *, qint32> prism::intersection_with_ray(ray *r) const
{
	qint32 l = polygon.length();
	vector2D e = r->get_emitter_pos();
	vector2D *nearest_intersection = 0;
	qreal nearest_dist = INFINITY;
	qint32 part;
	for(qint32 i = 0; i < l; i++)
	{
		vector2D p1 = polygon[i];
		vector2D p2 = polygon[(i+1)%l];
		vector2D *cur_intersect =
			common_functions::stretch_intersection(p1, p2, r);
		if (cur_intersect && (e.distance(*cur_intersect) < nearest_dist))
		{
			part = i;
			nearest_dist = e.distance(*cur_intersect);
			nearest_intersection = cur_intersect;
		}
	}

	return QPair<vector2D *, qint32>(nearest_intersection, part);
}

ray *prism::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;
	vector2D cross = *r->get_intersection_point();
	qint32 cross_num = r->get_intersection_part();
	return common_functions::generate_prism_ray
		(cross, normal[cross_num], index_of_refr, r, background);
}

qreal prism::get_distance_to_point(vector2D p) const
{
	if (test_ray(p, vector2D(1.0,0.0)))
		return 0.0; // point is inside

	qint32 l = polygon.length();
	qreal min = INFINITY;
	for (qint32 i = 0; i < l; i++)
	{
		qreal dist = common_functions::dist_to_stratch
				(polygon[i], polygon[(i+1)%l], p);
		if (dist < min) min = dist;
	}
	return min;
}

QString prism::who_i_am() const { return QString("Prism"); }

void prism::calculate_geometry()
{
	qint32 l = polygon.length();

	vector2D e1 = (polygon[0] + polygon[1%l]) / 2;
	vector2D n1;
	vector2D t(polygon[1%l] - polygon[0]);
	t /= t.length();
	n1.setX(-t.y());
	n1.setY(t.x());

	qint32 sign;
	if (test_ray(e1, n1)) sign = -1;
	else sign = 1;

	for (qint32 i = 0; i < l; i++)
	{
		vector2D tangent(polygon[(i+1)%l] - polygon[i]);
		vector2D n(-sign * tangent.y(), sign*tangent.x());
		normal.append(n / n.length());
	}
}

bool prism::test_ray(vector2D start, vector2D dir) const
{
	ray *trial_ray =
			new ray(start.x(), start.y(), dir, 0);

	qint32 l = polygon.length();
	qint32 count = 0;
	for (qint32 i = 0; i < l; i++)
	{
		vector2D p1 = polygon[i];
		vector2D p2 = polygon[(i+1)%l];

		if (common_functions::stretch_intersection(p1, p2, trial_ray))
			count++;
	}
	delete trial_ray;

	return count%2;
}

void prism::generate_outline()
{
	outline.moveTo(polygon[0]);
	qint32 l = polygon.length();
	for (qint32 i = 0; i < l; i++)
		outline.lineTo(polygon[i]);
	outline.lineTo(polygon[0]);
}
