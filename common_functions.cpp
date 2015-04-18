#include "common_functions.h"
#include "vector2D.h"
#include "ray.h"
#include <QPolygonF>
#include <QtMath>

vector2D *common_functions::stretch_intersection
	(vector2D edge_a, vector2D edge_b, ray* r)
{
	vector2D e = r->get_emitter_pos();
	vector2D d = r->get_direction_vect();

	qreal Dx = edge_b.x() - edge_a.x();
	qreal Dy = edge_b.y() - edge_a.y();

	qreal denominator = d.x() * Dy - d.y() * Dx;

	if (denominator == 0.0) return 0;	// if ray is parallel to the stratch

	qreal t = (e.y() - edge_a.y()) * Dx - (e.x() - edge_a.x()) * Dy;
	t /= denominator;

	if (t < 0.00001) return 0; // if ray is starting from the stratch
							// or after stretch

	vector2D cross;
	cross = e + d * t;

	// if cross is on the same line with the stratch,
	// but not between edge_a and edge_b - return 0

	vector2D tangent = edge_b - edge_a;
	qreal length = tangent.length();
	tangent /= length;
	qreal t1 = tangent.scalar_mult(cross - edge_a);
	if ( (t1 < 0.0) || (length < t1)) return 0;

	return new vector2D(cross);
}

qreal common_functions::dist_to_stratch
	(vector2D edge_a, vector2D edge_b, vector2D p)
{
	vector2D tangent(edge_b - edge_a);
	qreal l = tangent.length();
	tangent /= l;

	// s - the length of proection of (p-edge_a) on stretch
	qreal s = tangent.scalar_mult(p - edge_a);

	// if s too short or too long
	if (s < 0) return edge_a.distance(p);
	else if (s > l) return edge_b.distance(p);
	// else return the length of normal component of (p-edge_a)
	else
	{
		vector2D v(p - edge_a - s*tangent);
		return v.length();
	}
}

QPolygonF common_functions::regular_polygon
			(QPointF center, qreal radius,
			 quint32 vert_count, qreal rot)
{
	QPolygonF result;
	for (quint32 i = 0; i < vert_count; i++)
	{
		QPointF delta;
		qreal angle = 2 * i * M_PI / vert_count + rot;
		delta.setX(radius * qSin(angle));
		delta.setY(radius * qCos(angle));
		result << delta + center;
	}
	return result;
}

vector2D *common_functions::intersection_with_circle(QPointF center,
												qreal radius, ray *r)
{
	vector2D d = r->get_direction_vect();
	vector2D e = r->get_emitter_pos() - center;
	qreal C = d.vect_mult(e);

	qreal min_dist = qFabs(C);
	if (min_dist > radius) return 0;

	vector2D nearest_point(-d.y()*C, d.x()*C);
	qreal delta = qSqrt(radius*radius - C*C);

	vector2D p1( nearest_point + d*delta );
	vector2D p2( nearest_point - d*delta );

	qreal s1 = d.scalar_mult(p1 - e);
	qreal s2 = d.scalar_mult(p2 - e);
	if ( (s1 < 0.0) && (s2 < 0.0) ) return 0;

	vector2D result;
	if (s1 < s2 )
		if (s1 > 0.0) result = p1 + center;
		else result = p2 + center;
	else if (s2 > 0.0) result =  p2 + center;
		else result = p1 + center;

	return new vector2D(result);
}
