#ifndef CIRCLE_MIRROR_H
#define CIRCLE_MIRROR_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QPair>
class ray;
class field;
class QString;

class circle_mirror : public abstract_optics
{
	public:
		circle_mirror(vector2D edge_a, vector2D edge_b,
					  qreal radius, field *backg);
		~circle_mirror();

		QPair<vector2D *, qint32> intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		qreal get_distance_to_point(vector2D p) const;
		void setup_pen_and_brush();

		QString who_i_am() const;
		static const qint32 hatch_count = 15;

	private:
		void generate_outline();

		bool black_inside;
		qreal R, length, angle_a, angle_b, angle,
				radians_a, radians;
		vector2D center, edge_a, edge_b, r_a, r_b;
};

#endif // CIRCLE_MIRROR_H
