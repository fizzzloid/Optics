#ifndef SHPERE_H
#define SHPERE_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QPair>
class ray;
class field;

class sphere : public abstract_optics
{
	public:
		sphere(vector2D cntr, qreal r,
			   qreal index_of_refraction, field *backg);
		~sphere();

		QPair<vector2D *, qint32>intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

	private:
		void generate_outline();
		vector2D center;
		qreal radius;
		qreal index_of_refr;
};

#endif // SHPERE_H
