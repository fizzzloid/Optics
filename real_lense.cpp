#include "real_lense.h"
#include "vector2D.h"
#include "ray.h"
#include "common_functions.h"
#include "field.h"
#include <QList>
#include <QtMath>
#include <QPair>
#include <QString>
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
	center0 = 0.5 * (edge_b + edge_a);
	normal = (edge_b - edge_a) / length;

	// Not 1/2. Because.
	if (2 * qFabs(radius1) >= length) R1 = radius1;
	else if (radius1 >= 0) R1 = length * 0.500001;
	else R1 = - length / 0.500001;

	if (2 * qFabs(radius2) >= length) R2 = radius2;
	else if (radius2 >= 0) R2 = length / 0.500001;
	else R2 = - length / 0.500001;
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

	angle1 = angle_v_1a.angle() - angle_v_1b.angle();
	if (angle1 > 180.0) angle1 -= 360.0;
	else if (angle1 < -180.0) angle1 += 360.0;

	angle2 = angle_v_2b.angle() - angle_v_2a.angle();
	if (angle2 > 180.0) angle2 -= 360.0;
	else if (angle2 < -180) angle2 +=360;

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
		qDebug() << "something wrong:"
				 << "ray is intersecting non-existing part!";
		return 0;
		break;
	}

	return common_functions::generate_prism_ray
			(cross, n, index_of_refr, r, background);
}

qreal real_lense::get_distance_to_point(vector2D p) const
{
	qreal d1 = center1.distance(p) - qFabs(R1);
	qreal d2 = center2.distance(p) - qFabs(R2);
	bool f1 = (d1 <= 0.0) xor (R1 < 0.0);
	bool f2 = (d2 <= 0.0) xor (R2 < 0.0);
	bool f3 = vector2D(p - edge_a).scalar_mult(normal) >= 0;
	bool f4 = vector2D(p - edge_b).scalar_mult(normal) <= 0;

	if (f1 && f2 && f3 && f4) return 0.0;

	if (!f3) return common_functions::dist_to_stratch
					(corner_1a, corner_2a, p);
	else if (!f4) return common_functions::dist_to_stratch
					(corner_1b, corner_2b, p);
	else if (!f1) return qFabs(d1);
	else return qFabs(d2);

	return INFINITY;
}

QString real_lense::who_i_am() const { return QString("Real lense"); }

void real_lense::generate_outline()
{
	outline.moveTo(corner_1a);
	qreal abs = qFabs(R1);
	outline.arcTo(center1.x() - abs, center1.y() - abs,
				  2*abs, 2*abs, -angle_v_1a.angle(), angle1);
	abs = qFabs(R2);
	outline.arcTo(center2.x() - abs, center2.y() - abs,
				  2*abs, 2*abs, -angle_v_2b.angle(), angle2);
	outline.lineTo(corner_1a);
}
