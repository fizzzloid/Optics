#include "ray.h"
#include "linses.h"
#include "field.h"
#include <QList>
#include <QtMath>
#include <QDebug>

ray::ray(qreal xpos, qreal ypos, qreal dir, field *f, qreal intens)
{	
	emitter.setX(xpos);
	emitter.setY(ypos);

	parent = 0;
	child = 0;
	intersection_object = 0;
	intersection_point = 0;
	generator = 0;

	path = 0;
	set_intensity(intens);
	setup_colors();
	set_direction(dir);

	background = f;
	background->add_ray(this);
}

ray::ray(qreal xpos, qreal ypos, position dir_vect, field *f, qreal intens)
{
	emitter.setX(xpos);
	emitter.setY(ypos);

	path = 0;
	parent = 0;
	child = 0;
	intersection_object = 0;
	intersection_point = 0;
	generator = 0;

	set_intensity(intens);
	setup_colors();
	set_direction_vect(dir_vect);

	background = f;
	background->add_ray(this);
}

ray::~ray()
{
	if (path) delete path;
	if (child) delete child;
	if (parent && (parent->child == this)) parent->child = 0;
	if (generator) generator->delete_ray(this);
}

position ray::get_emitter_pos() const
{
	return emitter;
}

qreal ray::get_direction() const
{ return direction; }

position ray::get_direction_vect() const
{ return dir_vector; }

qreal ray::get_intensity() const
{ return intensity; }

void ray::set_emitter_pos(position emitter_pos)
{ emitter = emitter_pos; }

void ray::set_direction(qreal dir)
{
	direction = dir;
	dir_vector.setX(qCos(dir));
	dir_vector.setY(qSin(dir));
	generate_outline();
}

void ray::set_direction_vect(position dir_vect)
{
	dir_vector.setX(dir_vect.x());
	dir_vector.setY(dir_vect.y());
	dir_vector /= dir_vector.length();
	direction = qAtan(dir_vect.y() / dir_vect.x());
	if (dir_vect.x() < 0) direction += M_PI;
	generate_outline();
}

 void ray::set_intensity(qreal intens)
{ intensity = intens; }

 ray *ray::get_parent() const
{ return parent; }

 ray *ray::get_child() const
{ return child; }

void ray::set_child(ray *r)
{
	if (child) delete child;
	if (r)
	{
		r->parent = this;
		background->delete_ray(r);
	}
	child = r;
}

 field *ray::get_field() const
{ return background; }

bool ray::new_intersecting_object()
{
	QList<abstract_optics *> opt_list = background->get_optics();

	position *nearest_pos = 0;
	abstract_optics *nearest_object = 0;
	qreal nearest = INFINITY;

	position *tmp_pos = 0;
	abstract_optics *tmp_pointer = 0;

	qint32 l = opt_list.length();
	for (qint32 i = 0; i < l; i++)
	{
		tmp_pointer = opt_list[i];
		if ((tmp_pos = tmp_pointer->intersection_with_ray(this)) &&
			(tmp_pos->distance(emitter) < nearest) )
		{
			nearest = tmp_pos->distance(emitter);
			nearest_object = tmp_pointer;
			nearest_pos = tmp_pos;
		}
	}

	if (nearest_object == intersection_object) return false;

	intersection_object = nearest_object;
	intersection_point = nearest_pos;

	generate_outline();
	return true;
}

abstract_optics *ray::get_intersection_object() const
{
	return intersection_object;
}

position *ray::get_intersection_point() const
{
	return intersection_point;
}

 abstract_optics *ray::get_generator() const
{ return generator; }

void ray::set_generator(abstract_optics *o)
{
	generator = o;
}

QColor ray::get_color() const
{
	return color;
}

QPen ray::get_pen() const
{
	return pen;
}

QPen ray::get_emitter_pen() const
{
	return emitter_pen;
}

QBrush ray::get_emitter_brush() const
{
	return emitter_brush;
}

void ray::set_color(QColor c)
{
	color = c;
}

void ray::set_pen(QPen p)
{
	pen = p;
}

void ray::set_emitter_brush(QBrush b)
{
	emitter_brush = b;
}

void ray::set_emitter_pen(QPen p)
{
	emitter_pen = p;
}

QPainterPath ray::get_path() const
{
	return *path;
}

qreal ray::get_emitter_radius() const
{
	return emitter_radius;
}

void ray::setup_colors()
{
	color = Qt::red;
	color.setAlphaF(intensity);
	pen.setColor(color);
	pen.setWidthF(0.0);
	pen.setStyle(Qt::SolidLine);
	emitter_pen.setColor(color);
	emitter_pen.setWidthF(1.0);
	emitter_brush.setColor(color);
	emitter_brush.setStyle(Qt::SolidPattern);
	set_emitter_radius(3.0);
}

void ray::set_emitter_radius(qreal r)
{
	emitter_radius = r;
}

void ray::generate_outline()
{
	if (path) delete path;
	path = new QPainterPath;
	path->moveTo(emitter);
	if (intersection_point) path->lineTo(*intersection_point);
	else
	{
		position ray_end(qCos(direction), qSin(direction));
		ray_end *= ray::max_len;
		ray_end += emitter;
		path->lineTo(ray_end);
	}
}
