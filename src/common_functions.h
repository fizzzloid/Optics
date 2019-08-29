#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

class ray;
#include "vector2D.h"
class QPolygonF;
class QPointF;
class field;
class QPainterPath;
#include <QtGlobal>

namespace common_functions
{
	const vector2D v0(0.0, 0.0);
	vector2D *stretch_intersection
		(vector2D edge_a, vector2D edge_b, ray* r);

	qreal dist_to_stratch
		(vector2D edge_a, vector2D edge_b, vector2D p);

	QPolygonF regular_polygon(QPointF center, qreal radius,
							  quint32 vert_count, qreal rot = 0.0);

	vector2D *intersection_with_circle(QPointF center, qreal radius,
									  ray *r);
	ray *generate_prism_ray(vector2D cross, vector2D normal,
							qreal index_of_refr, ray *r, field *backg);

	vector2D *intersection_with_arc(QPointF center, qreal radius, ray *r,
									vector2D angle1 = v0, vector2D angle2 = v0);

}

#endif // COMMON_FUNCTIONS_H
