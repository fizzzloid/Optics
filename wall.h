#ifndef WALL_H
#define WALL_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QPair>
#include <QPainterPath>

class wall : public abstract_optics
{
	public:
		wall(vector2D start, vector2D end, field *backg);
		~wall();

		QPair<vector2D *, qint32> intersection_with_ray(ray *) const;

		qreal get_distance_to_point(vector2D p) const;

		void setup_pen_and_brush();

		static const qreal thickness = 0.005;
	private:
		void generate_outline();
		vector2D edge_a, edge_b, tangent, normal;
		qreal length;
};

#endif // WALL_H
