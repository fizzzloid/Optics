#ifndef ABSTRACTOPTICS_H
#define ABSTRACTOPTICS_H

#include <QList>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QPair>
class vector2D;
class ray;
class field;
class QString;

class abstract_optics
{
	public:
		abstract_optics(field *backg);
		virtual ~abstract_optics();

		virtual QPair<vector2D *, qint32> intersection_with_ray(ray *) const;
		virtual ray *generate_ray(ray *);

		QPainterPath get_outline() const;
		QPen get_pen() const;
		QBrush get_brush () const;

		virtual qreal get_distance_to_point(vector2D) const;
		virtual void setup_pen_and_brush();

		virtual QString who_i_am() const;

	protected:
		field *background;
		QPainterPath outline;
		QPen pen;
		QBrush brush;

		virtual void generate_outline();
};

#endif // ABSTRACTOPTICS_H
