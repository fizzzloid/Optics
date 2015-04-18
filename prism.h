#ifndef PRISM_H
#define PRISM_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QList>
#include <QPolygonF>
class field;
class ray;
class prism : public abstract_optics
{
	public:
		prism(QPolygonF p, qreal index_of_refraction, field *back);
		~prism();

		vector2D *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

	private:
		void calculate_geometry();
		void generate_outline();
		QPolygonF polygon;
		QList<vector2D> normal;
		qreal index_of_refr;
};

#endif // PRISM_H
