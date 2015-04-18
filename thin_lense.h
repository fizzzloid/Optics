#ifndef THIN_lense_H
#define THIN_lense_H

#include <abstractoptics.h>
#include <vector2D.h>
class thin_lense : public abstract_optics
{
	public:
		thin_lense(vector2D start, vector2D end, qreal dioptr, field *backg);
		thin_lense(vector2D cntr, vector2D norm, qreal radius,
				qreal dioptr, field *backg);
		~thin_lense();

		vector2D *intersection_with_ray(ray *r) const;
		ray *generate_ray(ray *r);

		void setup_pen_and_bruh();

	private:
		vector2D edge_a, edge_b, center, normal, tangent;
		qreal D, radius, angle;

		void generate_outline();
};

#endif // THIN_lense_H
