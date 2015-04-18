#include "sphere.h"
#include "field.h"
#include "vector2D.h"
#include "ray.h"
#include "common_functions.h"
#include <QtMath>

sphere::sphere(vector2D cntr, qreal r, field *backg)
	:abstract_optics(backg)
{
	center = cntr;
	radius = r;

	setup_pen_and_bruh();
	generate_outline();
}

sphere::~sphere() {}

vector2D *sphere::intersection_with_ray(ray *r) const
{
	return common_functions::intersection_with_circle
			(center, radius, r);
}

ray *sphere::generate_ray(ray *r)
{
	if ()
}

void sphere::generate_outline()
{
	outline.addEllipse(center, radius, radius);
}
