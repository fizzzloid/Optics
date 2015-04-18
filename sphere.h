#ifndef SHPERE_H
#define SHPERE_H

#include "abstractoptics.h"
#include "vector2D.h"
class ray;
class field;

class sphere : public abstract_optics
{
	public:
		sphere(vector2D cntr, qreal r, field *backg);
		~sphere();

		vector2D *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

	private:
		void generate_outline();
		vector2D center;
		qreal radius;
};

#endif // SHPERE_H
