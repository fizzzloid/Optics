#ifndef PRISM_H
#define PRISM_H

#include "abstractoptics.h"
#include "position.h"
#include <QList>
#include <QPolygonF>
class field;
class ray;
class prism : public abstract_optics
{
	public:
		prism(QPolygonF p, qreal index_of_refraction, field *back);
		~prism();

		position *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		QPolygonF operator <<(QPolygonF &p);
		QPolygonF operator <<(QPointF &p);

	private:
		void generate_outline();
		QPolygonF polygon;
		qreal index_of_refr;
};

#endif // PRISM_H
