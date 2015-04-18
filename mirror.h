#ifndef MIRROR_H
#define MIRROR_H

#include <abstractoptics.h>
#include "position.h"

class mirror : public abstract_optics
{
	public:
		mirror(position start, position end, bool orient,  field *backg);
		~mirror();

		position *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		static const quint32 hatch_count = 15;

	private:
		position edge_a, edge_b, normal, tangent;
		field *background;
		qreal length;

		void generate_outline();


};

#endif // MIRROR_H
