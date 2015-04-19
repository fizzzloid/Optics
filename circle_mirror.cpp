#include "circle_mirror.h"
#include "ray.h"
#include "field.h"
#include <QtMath>

circle_mirror::circle_mirror(vector2D a, vector2D b,
							 qreal radius, field *backg)
	:abstract_optics(backg)
{
	edge_a = a;
	edge_b = b;
	R = radius;

	vector2D tang(edge_b - edge_a);
	vector2D n(tang.x(), -tang.y());

	center = 0.5 * (edge_a + edge_b) + n * radius;

	angle_a = (edge_a - center).angle();
	angle_b = (edge_b - center).angle();
	length = M_PI * radius * qFabs(angle_a - angle_b) / 180.0;

	setup_pen_and_brush();
	generate_outline();
}

circle_mirror::~circle_mirror() {}

QPair<vector2D *, qint32> intersection_with_ray(ray *r) const
{
	return QPair<vector2D *, qint32>(0,0);
}

ray *circle_mirror::generate_ray(ray *r)
{
	return 0;
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
	cir
}
