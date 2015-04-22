#ifndef PRISM_H
#define PRISM_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QList>
#include <QPolygonF>
#include <QPair>
class field;
class ray;
class prism : public abstract_optics
{
	public:
		prism(QPolygonF p, qreal index_of_refraction, field *back);
		~prism();

		QPair<vector2D *, qint32> intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		qreal get_distance_to_point(vector2D p) const;

	private:
		void calculate_geometry();		
		bool test_ray(vector2D start, vector2D dir) const; // is directed outside
		void generate_outline();

		QPolygonF polygon;
		QList<vector2D> normal;
		qreal index_of_refr;
};

#endif // PRISM_H
