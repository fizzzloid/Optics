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
	cross.setX(e.x() + d.x() * t);
	cross.setY(e.y() + d.y() * t);

	// if cross is on the same line with the stratch,
	// but not between edge_a and edge_b - return 0
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
	else return 0;

	return new position(cross);
}

