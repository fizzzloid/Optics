#include "real_lense.h"
#include "vector2D.h"
#include "ray.h"
#include "common_functions.h"
#include "field.h"
#include <QList>
#include <QtMath>
#include <QPair>
#include <QDebug>
real_lense::real_lense(vector2D a, vector2D b,
						qreal thicknes,
						qreal radius1, qreal radius2,
						qreal index_of_refraction, field *backg)
				: abstract_optics(backg)
{
	edge_a = a;
	edge_b = b;
	length = edge_a.distance(edge_b);
	center0 = (edge_b + edge_a) / 2.0;
	normal = (edge_b - edge_a) / length;

	// Not two. Because.
	if (2 * qFabs(radius1) >= length) R1 = radius1;
	else if (radius1 >= 0) R1 = length / 1.99999;
	else R1 = - length / 1.99999;

	if (2 * qFabs(radius2) >= length) R2 = radius2;
	else if (radius2 >= 0) R2 = length / 1.99999;
	else R2 = - length / 1.99999;
	thick = thicknes;
	index_of_refr = index_of_refraction;

	tangent.setX(-normal.y());
	tangent.setY(normal.x());

	qint32 sign;
	if (R1 >= 0) sign = 1;
	else sign = -1;
	center1 = center0 + tangent
			* (thick / 2 - sign * qSqrt(R1*R1 - length*length / 4));

	if (R2 >= 0) sign = 1;
	else sign = -1;
	center2 = center0 - tangent
			* (thick / 2 - sign * qSqrt(R2*R2 - length*length / 4));

	corner_1a = edge_a + 0.5 * thick * tangent;
	corner_1b = edge_b + 0.5 * thick * tangent;
	corner_2a = edge_a - 0.5 * thick * tangent;
	corner_2b = edge_b - 0.5 * thick * tangent;

	angle_v_1a = corner_1a - center1;
	angle_v_1b = corner_1b - center1;
	angle_v_2a = corner_2a - center2;
	angle_v_2b = corner_2b - center2;

	setup_pen_and_brush();
	generate_outline();
}

real_lense::~real_lense() {}

QPair<vector2D *, qint32> real_lense::intersection_with_ray
											(ray *r) const
{
	QList<vector2D *> crosses;
	crosses.append(common_functions::stretch_intersection
					(corner_1a, corner_2a, r));
	crosses.append(common_functions::intersection_with_arc
				   (center1, R1, r,
					angle_v_1a, angle_v_1b));
	crosses.append(common_functions::stretch_intersection
				   (corner_1b, corner_2b, r));
	crosses.append(common_functions::intersection_with_arc
				   (center2, R2, r,
					angle_v_2a, angle_v_2b));

	vector2D *cross = 0;
	vector2D e(r->get_emitter_pos());
	qreal min_dist = INFINITY;
	qint32 part = -1;
	qreal cur_dist;
	for (qint32 i = 0; i < 4; i++)
		if ( crosses[i] &&
		   ( (cur_dist = crosses[i]->distance(e)) < min_dist))
		{
			min_dist = cur_dist;
			cross = crosses[i];
			part = i;
		}
	return QPair<vector2D *, qint32> (cross, part);
}

ray *real_lense::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;
	vector2D cross = *r->get_intersection_point();
	qint32 inter_part = r->get_intersection_part();

	vector2D n;
	switch (inter_part)
	{
	case 0:
		n = -normal;
		break;
	case 2:
		n = normal;
		break;
	case 1:
		n = (cross - center1) / R1;
		break;
	case 3:
		n = (cross - center2) / R2;
		break;
	default:
		qDebug() << "something wrong: ray is intersecting non-existin part!";
		return 0;
		break;
	}

	return common_functions::generate_prism_ray
			(cross, n, index_of_refr, r, background);
}

void real_lense::generate_outline()
{
	outline.moveTo(corner_2a);
//	outline.lineTo(corner_1a);

	qreal abs = qFabs(R1);
	if (R1 >= 0) outline.arcTo(center1.x() - abs,
							center1.y() - abs,
							2*abs, 2*abs,  angle_v_1a.angle(),
							angle_v_1b.angle() - angle_v_1a.angle());
	else outline.arcTo(center1.x() - abs,
					  center1.y() - abs,
					  2*abs, 2*abs,  -angle_v_1a.angle(),
					  angle_v_1a.angle() - angle_v_1b.angle());

//	outline.lineTo(corner_2b);
	abs  = qFabs(R2);
	if (R2 >= 0) outline.arcTo(center2.x() - abs,
							  center2.y() - abs,
							  2*abs, 2*abs, -angle_v_2b.angle(),
							  angle_v_2b.angle() - angle_v_2a.angle());
	else outline.arcTo(center2.x() - abs,
					   center2.y() - abs,
					   2*abs, 2*abs, angle_v_2b.angle(),
					   angle_v_2a.angle() - angle_v_2b.angle());

}
