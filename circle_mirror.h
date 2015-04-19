#ifndef CIRCLE_MIRROR_H
#define CIRCLE_MIRROR_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QPair>
class ray;
class field;

class circle_mirror : public abstract_optics
{
	public:
		circle_mirror(vector2D edge_a, vector2D edge_b,
					  qreal radius, field *backg);
		~circle_mirror();

		QPair<vector2D *, qint32> intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		void setup_pen_and_brush();

	private:
		void generate_outline();

		qreal R, length, angle_a, angle_b;
		vector2D center, edge_a, edge_b;
};

#endif // CIRCLE_MIRROR_H
