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

		static const qint32 hatch_count = 15;

	private:
		void generate_outline();

		qreal R, length, angle_a, angle_b, angle,
				radians_a, radians;
		vector2D center, edge_a, edge_b, r_a, r_b, main_tangent;
};

#endif // CIRCLE_MIRROR_H
