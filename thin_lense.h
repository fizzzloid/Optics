#ifndef THIN_lense_H
#define THIN_lense_H

#include <abstractoptics.h>
#include <position.h>
class thin_lense : public abstract_optics
{
	public:
		thin_lense(position start, position end, qreal dioptr, field *backg);
		thin_lense(position cntr, position norm, qreal radius,
				qreal dioptr, field *backg);
		~thin_lense();

		position *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		void setup_pen_and_bruh();

	private:
		position edge_a, edge_b, center, normal, tangent;
		qreal D, radius, angle;

		void generate_outline();
};

#endif // THIN_lense_H
