#include "real_lense.h"
#include "vector2D.h"
#include "ray.h"
#include "common_functions.h"
#include "field.h"
#include <QList>
#include <QtMath>

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
	R1 = qMax(radius1, length / 2.0);
	R2 = qMax(radius2, length / 2.0);
	thick = thicknes;
	index_of_refr = index_of_refraction;

	tangent.setX(normal.y());
	tangent.setY(-normal.x());

	center1 = center0
			- tangent * (R1 + thick / 2);
	center2 = center0
			+ tangent * (R2 + thick / 2);

	corner_1a = edge_a - 0.5 * thick * tangent;
	corner_1b = edge_b - 0.5 * thick * tangent;
	corner_2a = edge_a + 0.5 * thick * tangent;
	corner_2b = edge_b + 0.5 * thick * tangent;

	angle_v_1a = corner_1a - center1;
	angle_v_1b = corner_1b - center1;
	angle_v_2a = corner_2a - center2;
	angle_v_2b = corner_2b - center2;

	setup_pen_and_bruh();
	generate_outline();
}

real_lense::~real_lense() {}

vector2D *real_lense::intersection_with_ray(ray *r) const
{
	QList<vector2D *> crosses;
	crosses.append(common_functions::stretch_intersection
					(corner_1a, corner_1b, r));
	crosses.append(common_functions::stretch_intersection
				   (corner_2a, corner_2b, r));
	crosses.append(common_functions::intersection_with_arc
				   (center1, R1, r,
					angle_v_1a, angle_v_1b));
	crosses.append(common_functions::intersection_with_arc
				   (center2, R2, r,
					angle_v_2a, angle_v_2b));

	vector2D *cross;
	vector2D e(r->get_emitter_pos());
	qreal min_dist = INFINITY;
	qreal cur_dist;
	for (qint32 i = 0; i < 4; i++)
		if (crosses[i] &&
				((cur_dist = crosses[i]->distance(e)) < min_dist))
		{
			min_dist = cur_dist;
			cross = crosses[i];
		}
	return cross;
}

ray *real_lense::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;
	vector2D cross = *r->get_intersection_point();
	return 0;
}

void real_lense::generate_outline()
{
	outline.moveTo(corner_2a);
	outline.lineTo(corner_1a);

	outline.quadTo(center1 + tangent * R1 / 2, corner_1b);
	outline.lineTo(corner_2b);
	outline.quadTo(center2 - tangent * R2 / 2, corner_2a);

	outline.addEllipse(center2, 0.01, 0.01);
}
