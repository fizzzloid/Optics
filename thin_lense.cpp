#include "thin_lense.h"
#include "ray.h"
#include "field.h"
#include <QtMath>
#include <QPainter>
#include <common_functions.h>

thin_lense::thin_lense(position start, position end,
					   qreal dioptr, field *backg) : abstract_optics(backg)
{
	edge_a.setX(start.x());
	edge_a.setY(start.y());
	edge_b.setX(end.x());
	edge_b.setY(end.y());

	center.setX(edge_a.x() + edge_b.x());
	center.setY(edge_a.y() + edge_b.y());
	center /= 2.0;
	radius = edge_a.distance(edge_b) / 2.0;

	tangent.setX(edge_a.x() - edge_b.x());
	tangent.setY(edge_a.y() - edge_b.y());
	tangent /= 2 * radius;

	normal.setX(-tangent.y());
	normal.setY(tangent.x());
	angle = qAsin(normal.y() / normal.length());
	D = dioptr;

	setup_pen_and_bruh();
	generate_outline();
}

thin_lense::thin_lense(position cntr, position norm, qreal r,
					   qreal dioptr, field *backg) : abstract_optics(backg)
{
	center.setX(cntr.x());
	center.setY(cntr.y());
	normal.setX(norm.x());
	normal.setY(norm.y());
	normal /= normal.length();

	radius = r;
	D = dioptr;

	edge_a.setX(center.x() - normal.y()*r);
	edge_a.setY(center.y() + normal.x()*r);
	edge_b.setX(center.x() + normal.y()*r);
	edge_b.setY(center.y() - normal.x()*r);

	angle = qAcos(normal.x() / normal.length());

	setup_pen_and_bruh();
	generate_outline();
}

thin_lense::~thin_lense() {}

position *thin_lense::intersection_with_ray(ray *r) const
{
	return common_functions::stretch_intersection(edge_a, edge_b, r);
}

ray *thin_lense::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_brigh) return 0;
	if (r->get_intersection_object() != this) return 0;
	position cross = *r->get_intersection_point();

	qreal R = center.distance(cross);
	if (cross.distance(edge_a) > cross.distance(edge_b)) R *= -1;

	/* 1/u + 1/v = D
	 * k = R/u
	 * u = R*ctg(alpha)
	 * v = b*ctg(betta)
	 */

	position d = r->get_direction_vect();

	// sin_alpha = [d,n]/(|d|*|n|); |d| = |n| = 1
	qreal sin_alpha = d.vect_mult(normal);
	// tan_alpha = sin/cos = sin/sqrt(1-sin^2)
	qreal tan_alpha;
	if (sin_alpha != 1.0)
		tan_alpha = sin_alpha/qSqrt(1-sin_alpha*sin_alpha);
	else return 0;
	qreal betta = qAtan(R*D - tan_alpha);

	ray *new_ray = new ray(cross.x(), cross.y(), betta + angle,
						   background, r->get_intensity() - ray::bright_step);
	if ( normal.scalar_mult(d)
		*normal.scalar_mult(new_ray->get_direction_vect()) < 0)
			new_ray->set_direction(M_PI - betta);

	r->set_child(new_ray);
	generated_rays.append(new_ray);

	return new_ray;
}

void thin_lense::setup_pen_and_bruh()
{
	pen.setColor(Qt::blue);
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);

	QColor brush_color(Qt::darkBlue);
	brush_color.setAlphaF(0.0);
	brush.setColor(brush_color);
	brush.setStyle(Qt::SolidPattern);
}

void thin_lense::generate_outline()
{
	outline.moveTo(edge_a);
	outline.lineTo(edge_b);

	qreal k;
	if (D >= 0.0 ) k = radius * 0.1;
	else k = -radius * 0.1;

	position whisker_a1(tangent);
	whisker_a1 += normal;
	whisker_a1 *= k;
	whisker_a1 += edge_a;

	position whisker_a2(whisker_a1);
	whisker_a2 -= normal * 2 * k;

	position whisker_b1(tangent);
	whisker_b1 += normal;
	whisker_b1 *= -k;
	whisker_b1 += edge_b;

	position whisker_b2(whisker_b1);
	whisker_b2 += normal * 2 * k;

	outline.moveTo(whisker_a1);
	outline.lineTo(edge_a);
	outline.lineTo(whisker_a2);
	outline.moveTo(whisker_b1);
	outline.lineTo(edge_b);
	outline.lineTo(whisker_b2);
}