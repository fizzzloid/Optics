#ifndef MIRROR_H
#define MIRROR_H

#include <abstractoptics.h>
#include "vector2D.h"
#include <QPair>

class mirror : public abstract_optics
{
	public:
		mirror(vector2D start, vector2D end, bool orient,  field *backg);
		~mirror();

		QPair<vector2D *, qint32> intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		qreal get_distance_to_point(vector2D p) const;

		static const quint32 hatch_count = 15;

	private:
		vector2D edge_a, edge_b, normal, tangent;
		qreal length;

		void generate_outline();


};

#endif // MIRROR_H
