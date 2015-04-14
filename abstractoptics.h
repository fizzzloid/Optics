#ifndef ABSTRACTOPTICS_H
#define ABSTRACTOPTICS_H

#include <QList>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
class position;
class ray;
class field;

class abstract_optics
{
	public:
		abstract_optics(field *backg);
		virtual ~abstract_optics();

		virtual position *intersection_with_ray(ray *) const;
		virtual ray *generate_ray(ray *);

		QList<ray *> get_generated_rays() const;
		void delete_ray(ray *r);
		QPainterPath get_outline() const;
		QPen get_pen() const;
		QBrush get_brush () const;

		virtual void setup_pen_and_bruh();

	protected:
		QList<ray *> generated_rays;
		field *background;
		QPainterPath outline;
		QPen pen;
		QBrush brush;

		virtual void generate_outline();
};

#endif // ABSTRACTOPTICS_H
