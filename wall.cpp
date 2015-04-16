#include "wall.h"
#include "common_functions.h"

wall::wall(position start, position end, field *backg) :
	abstract_optics(backg)
{
	edge_a = start;
	edge_b = end;
	tangent.setX(edge_a.x() - edge_b.x());
	tangent.setY(edge_a.y() - edge_b.y());
	tangent /= length = tangent.length();

	normal.setX(tangent.y());
	normal.setY(-tangent.x());

	setup_pen_and_bruh();
	generate_outline();
}

wall::~wall() {}

position *wall::intersection_with_ray(ray *r) const
{
	return common_functions::stretch_intersection(edge_a, edge_b, r);
}

void wall::generate_outline()
{
	position p1(edge_a + normal * length * thickness);
	position p2(edge_a - normal * length * thickness);
	position p3(edge_b - normal * length * thickness);
	position p4(edge_b + normal * length * thickness);

	outline.moveTo(p1);
	outline.lineTo(p2);
	outline.lineTo(p3);
	outline.lineTo(p4);
	outline.lineTo(p1);
}

void wall::setup_pen_and_bruh()
{
	pen.setColor(Qt::darkGray);
	pen.setWidthF(0.0);
	pen.setStyle(Qt::SolidLine);

	brush.setColor(Qt::gray);
	brush.setStyle(Qt::SolidPattern);
}
