#include "abstractoptics.h"
#include "vector2D.h"
#include "ray.h"
#include "field.h"
#include <QPainterPath>
#include <QPair>
#include <QtMath>
#include <QString>

abstract_optics::abstract_optics(field *backg)
{
	background = backg;
	background->add_optic(this);
	setup_pen_and_brush();
}

abstract_optics::~abstract_optics() {}

QPair<vector2D *, qint32> abstract_optics::intersection_with_ray(ray *) const
{
	return QPair<vector2D *, qint32>(0,0);
}

ray *abstract_optics::generate_ray(ray *) { return 0; }
QPainterPath abstract_optics::get_outline() const { return outline; }
QBrush abstract_optics::get_brush() const {	return brush; }
QPen abstract_optics::get_pen() const { return pen; }
qreal abstract_optics::get_distance_to_point
						(vector2D) const { return INFINITY; }

void abstract_optics::setup_pen_and_brush()
{
	pen.setColor(Qt::blue);
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);

	QColor brush_color(Qt::darkBlue);
	brush_color.setAlphaF(0.3);
	brush.setColor(brush_color);
	brush.setStyle(Qt::SolidPattern);
}

void abstract_optics::set_pen_color(QColor c) { pen.setColor(c); }
void abstract_optics::set_brush_color(QColor c) { brush.setColor(c); }

void abstract_optics::move_to(qreal, qreal) {}
void abstract_optics::move_by(qreal, qreal) {}
void abstract_optics::rot_by(qreal) {}
void abstract_optics::set_angle(qreal) {}
void abstract_optics::set_nodal_points(QList<vector2D>) {}

qreal abstract_optics::get_angle() const { return 0.0; }
QList<vector2D> abstract_optics::get_nodal_points() const { return QList<vector2D>(); }

QString abstract_optics::who_i_am() const
{
	return QString("abstract optics");
}

void abstract_optics::generate_outline() {}
