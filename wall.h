#ifndef WALL_H
#define WALL_H

#include "abstractoptics.h"
#include "position.h"
#include <QPainterPath>

class wall : public abstract_optics
{
	public:
		wall(position start, position end, field *backg);
		~wall();

		position *intersection_with_ray(ray *) const;

		void setup_pen_and_bruh();

		static const qreal thickness = 0.005;
	private:
		void generate_outline();
		position edge_a, edge_b, tangent, normal;
		qreal length;
};

#endif // WALL_H
