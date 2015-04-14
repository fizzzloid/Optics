#include "ray.h"
#include "linses.h"
#include "field.h"
#include <QList>
#include <QtMath>

ray::ray(qreal xpos, qreal ypos, qreal dir, field *f, qreal intens)
{	
	emitter.setX(xpos);
	emitter.setY(ypos);
	direction = dir;
	intensity = intens;
	dir_vector.setX(qCos(dir));
	dir_vector.setY(qSin(dir));

	parent = 0;
	child = 0;
	intersection_object = 0;
	intersection_point = 0;
	generator = 0;

	background = f;
	background->add_ray(this);
}

ray::ray(qreal xpos, qreal ypos, position dir_v, field *f, qreal intens)
{
	emitter.setX(xpos);
	emitter.setY(ypos);
	intensity = intens;
	dir_vector.setX(dir_v.x());
	dir_vector.setY(dir_v.y());
	dir_vector /= dir_vector.length();
	direction = qAtan(dir_v.y() / dir_v.x());
	if (dir_v.x() < 0) direction += M_PI;

	parent = 0;
	child = 0;
	intersection_object = 0;
	intersection_point = 0;
	generator = 0;

	background = f;
	background->add_ray(this);
}

ray::~ray()
{
	if (child) delete child;
	if (parent && (parent->get_child() == this)) parent->set_child(0);
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

inline qreal ray::get_intensity() const
{ return intensity; }

inline void ray::set_emitter_pos(position emitter_pos)
{ emitter = emitter_pos; }

inline void ray::set_direction(qreal dir)
{ direction = dir; }

inline void ray::set_direction_vect(position dir_vect)
{
	dir_vector.setX(dir_vect.x());
	dir_vector.setY(dir_vect.y());
}

inline void ray::set_intensity(qreal intens)
{ intensity = intens; }

inline ray *ray::get_parent() const
{ return parent; }

inline ray *ray::get_child() const
{ return child; }

void ray::set_parent(ray *r)
{
	ray *p = parent;
	parent = r;
	if (p && (p->get_child() == this)) p->set_child(0);
	parent->set_child(this);
}

void ray::set_child(ray *r)
{
	if (child) delete child;
	child = r;
	child->set_parent(this);
}

inline field *ray::get_field() const
{ return background; }

bool ray::new_intersecting_object()
{
	QList<abstract_optics *> opt_list = background->get_optics();

	position *nearest_pos = 0;
	abstract_optics *nearest_object = 0;
	qreal nearest = INFINITY;

	position *tmp_pos = 0;
	abstract_optics *tmp_pointer = 0;

	quint32 l = opt_list.length();
	for (quint32 i = 0; i < l; i++)
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

inline abstract_optics *ray::get_generator() const
{ return generator; }

void ray::set_generator(abstract_optics *o)
{
	generator = o;
}
