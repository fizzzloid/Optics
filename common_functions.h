#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

class ray;
class vector2D;
class QPolygonF;
class QPointF;
#include <QtGlobal>

namespace common_functions
{
	vector2D *stretch_intersection
		(vector2D edge_a, vector2D edge_b, ray* r);

	qreal dist_to_stratch
		(vector2D edge_a, vector2D edge_b, vector2D p);

	QPolygonF regular_polygon(QPointF center, qreal radius,
							  quint32 vert_count, qreal rot = 0.0);

	vector2D *intersection_with_circle(QPointF center, qreal radius,
									  ray *r);
}

#endif // COMMON_FUNCTIONS_H
