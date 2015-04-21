#include "circle_mirror.h"
#include "ray.h"
#include "field.h"
#include "common_functions.h"
#include <QtMath>
#include <QDebug>
circle_mirror::circle_mirror(vector2D a, vector2D b,
							 qreal radius, field *backg)
	:abstract_optics(backg)
{
	edge_a = a;
	edge_b = b;


	vector2D main_tangent = edge_b - edge_a;
	qreal dist = main_tangent.length();
	main_tangent /= dist;
	if (2*qFabs(radius) > dist ) R = radius;
	else if (radius > 0) R = 0.5001*dist;
	else R = - 0.5001*dist ;


	vector2D n(-main_tangent.y(), main_tangent.x());

	center = 0.5 * (edge_a + edge_b);
	if (black_inside = (R > 0))
		center += n * qSqrt(R*R - dist * dist / 4);
	else
		center -= n * qSqrt(R*R - dist * dist / 4);

	r_a = edge_a - center;
	r_b = edge_b - center;
	angle_a = r_a.angle();
	angle_b = r_b.angle();
	angle = angle_a - angle_b;

	if (angle > 180.0) angle -= 360.0;
	else if (angle < -180.0) angle += 360;
	length = M_PI * R * qFabs(angle) / 180.0;

	radians_a = qDegreesToRadians(angle_a);
	radians = qDegreesToRadians(angle);


	setup_pen_and_brush();
	generate_outline();
}

circle_mirror::~circle_mirror() {}

QPair<vector2D *, qint32> circle_mirror::intersection_with_ray(ray *r) const
{
	vector2D *v = common_functions::intersection_with_arc
			(center, R, r, r_a, r_b);

	return QPair<vector2D *, qint32>(v,0);
}

ray *circle_mirror::generate_ray(ray *r)
{
	if (r->get_intensity() < ray::min_intensity) return 0;
	if (r->get_intersection_object() != this) return 0;

	vector2D cross = *r->get_intersection_point();
	vector2D normal = (cross - center) / R;
	vector2D dir = r->get_direction_vect();
	// if ray is coming from "black" side of mirror
	if ((vector2D(cross - center).scalar_mult(dir) > 0)
			^ black_inside) return 0;

	vector2D new_dir = dir;
	new_dir -= 2 * normal * normal.scalar_mult(dir);

	ray *new_ray = new ray(cross.x(), cross.y(), new_dir,
						   background,
						   r->get_intensity() - ray::intensity_step);
	r->set_child(new_ray);
	return new_ray;
}

void circle_mirror::setup_pen_and_brush()
{
	pen.setColor(Qt::blue);
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);

	QColor brush_color(Qt::darkBlue);
	brush_color.setAlpha(0);
	brush.setColor(brush_color);
	brush.setStyle(Qt::SolidPattern);
}

void circle_mirror::generate_outline()
{
	outline.moveTo(edge_a);
	qreal abs = qFabs(R);
	outline.arcTo(center.x() - abs, center.y() - abs,
				  2*abs, 2*abs, -angle_a, angle);

	for (qint32 i = 0; i < circle_mirror::hatch_count; i++)
	{
		vector2D hatch_start;
		qreal t = - i * radians / hatch_count;
		hatch_start.setX(R*qCos(radians_a + t));
		hatch_start.setY(R*qSin(radians_a + t));
		if (R < 0) hatch_start *= -1;

		vector2D n = hatch_start / hatch_start.length();
		vector2D tang(-n.y(), n.x());
		vector2D hatch_delta = (0.7*n + tang)*length *0.05;
		hatch_start += center;
		outline.moveTo(hatch_start);
		outline.lineTo(hatch_start + hatch_delta);
	}
}
