#include "common_functions.h"
#include "position.h"
#include "ray.h"

position *common_functions::stretch_intersection
	(position edge_a, position edge_b, ray* r)
{
	position e = r->get_emitter_pos();
	position d = r->get_direction_vect();

	qreal Dx = edge_b.x() - edge_a.x();
	qreal Dy = edge_b.y() - edge_a.y();

	qreal denominator = d.x() * Dy - d.y() * Dx;

	if (denominator == 0.0) return 0;	// if ray is parallel to the stratch

	qreal t = (e.y() - edge_a.y()) * Dx - (e.x() - edge_a.x()) * Dy;
	t /= denominator;

	if (t < 0.00001) return 0; // if ray is starting from the stratch
							// or after stretch

	position cross;
	cross = e + d * t;

	// if cross is on the same line with the stratch,
	// but not between edge_a and edge_b - return 0

	position tangent = edge_b - edge_a;
	qreal length = tangent.length();
	tangent /= length;
	qreal t1 = tangent.scalar_mult(cross - edge_a);
	if ( (t1 < 0.0) || (length < t1)) return 0;
/*
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
	else return 0; */

	return new position(cross);
}

qreal common_functions::dist_to_stratch
	(position edge_a, position edge_b, position p)
{
	position tangent(edge_b - edge_a);
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
		position v(p - edge_a - s*tangent);
		return v.length();
	}
}

