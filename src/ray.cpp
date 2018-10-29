#include "ray.h"
#include "lenses.h"
#include "field.h"
#include "common_functions.h"
#include <QList>
#include <QPair>
#include <QtMath>
#include <QDebug>

using namespace ray_prop;

ray::ray(qreal xpos, qreal ypos, qreal dir, field *f, qreal intens)
	: emitter(xpos, ypos),
	  parent(0),
	  child(0),
	  intersection_object(0),
	  intersection_point(0),
	  generator(0),
	  path(0),
	  background(f)

{	
	set_intensity(intens);
	setup_colors();
	set_direction(dir);
	if (background) background->add_ray(this);
}

ray::ray(qreal xpos, qreal ypos, vector2D dir_vect, field *f, qreal intens)
	: emitter(xpos, ypos),
	  path(0),
	  parent(0),
	  child(0),
	  intersection_object(0),
	  intersection_point(0),
	  generator(0),
	  background(f)
{
	set_intensity(intens);
	setup_colors();
	set_direction_vect(dir_vect);
	if (background) background->add_ray(this);
}

ray::~ray()
{
	if (path) delete path;
	if (child) delete child;
	if (parent && (parent->child == this)) parent->child = 0;
}

vector2D ray::get_emitter_pos() const { return emitter; }
qreal ray::get_direction() const { return direction; }
vector2D ray::get_direction_vect() const { return dir_vector; }
qreal ray::get_intensity() const { return intensity; }
void ray::set_emitter_pos(vector2D emitter_pos) { emitter = emitter_pos; }

void ray::set_direction(qreal dir)
{
	direction = dir;
	dir_vector.setX(qCos(dir));
	dir_vector.setY(qSin(dir));
	generate_outline();
}

void ray::set_direction_vect(vector2D dir_vect)
{
	dir_vector = dir_vect / dir_vect.length();
	direction = qAcos(dir_vect.x());
	if (dir_vect.y() < 0) direction *= -1;
	generate_outline();
}

void ray::set_intensity(qreal intens) { intensity = qMin(intens, 1.0); }
ray *ray::get_parent() const { return parent; }
ray *ray::get_child() const { return child; }

void ray::set_child(ray *r)
{
	if (child == r) return;
	if (child) delete child;
	if (r)
	{
		r->parent = this;
		background->delete_ray(r);
	}
	child = r;
}

field *ray::get_field() const { return background; }

bool ray::new_intersecting_object()
{
	QList<abstract_optics *> opt_list = background->get_optics();

	vector2D *nearest_pos = 0;
	qint32 part;
	abstract_optics *nearest_object = 0;
	qreal nearest = INFINITY;

	QPair<vector2D *, qint32> inter_info;
	abstract_optics *tmp_opt = 0;

	qint32 l = opt_list.length();
	for (qint32 i = 0; i < l; i++)
	{
		tmp_opt = opt_list[i];
		inter_info = tmp_opt->intersection_with_ray(this);
		if ((inter_info.first ) &&
			(inter_info.first->distance(emitter) < nearest) )
		{
			nearest = inter_info.first->distance(emitter);
			nearest_object = tmp_opt;
			nearest_pos = inter_info.first;
			part = inter_info.second;
		}
		else if (inter_info.first) delete inter_info.first;
	}

	bool f1 = nearest_object == intersection_object;
	bool f2 = !(nearest_pos && intersection_point);
	bool f3 = nearest_pos && intersection_point
			&& (*nearest_pos == *intersection_point);
	bool f4 = intersection_part == part;
	if (f1 && f2 && f3 && f4) return false;

	intersection_object = nearest_object;
	intersection_point = nearest_pos;
	intersection_part = part;

	generate_outline();
	return true;
}

abstract_optics *ray::get_intersection_object() const { return intersection_object; }
vector2D *ray::get_intersection_point() const { return intersection_point; }
qint32 ray::get_intersection_part() const { return intersection_part; }
abstract_optics *ray::get_generator() const { return generator; }
void ray::set_generator(abstract_optics *o) { generator = o; }
QColor ray::get_color() const { return color; }
QPen ray::get_pen() const {	return pen; }
QPen ray::get_emitter_pen() const {	return emitter_pen; }
QBrush ray::get_emitter_brush() const {	return emitter_brush; }

void ray::set_color(QColor c)
{
	pen.setColor(color = c);
	if (child) child->set_color(c);
}

void ray::set_pen(QPen p) {	pen = p; }
void ray::set_emitter_brush(QBrush b) {	emitter_brush = b; }
void ray::set_emitter_pen(QPen p) {	emitter_pen = p; }
QPainterPath ray::get_path() const { return *path; }
qreal ray::get_emitter_radius() const {	return emitter_radius; }

qreal ray::get_distance_to_point(vector2D p) const
{
	qreal min = INFINITY;
	ray *cur_ray = (ray *) this;
	while (cur_ray)
	{
		qreal dist;
		if (cur_ray->intersection_point)
			dist = common_functions::dist_to_stratch
				(cur_ray->emitter, *cur_ray->intersection_point, p);
		else dist = common_functions::dist_to_stratch
				(cur_ray->emitter,
				 cur_ray->emitter + cur_ray->dir_vector * max_len, p);

		if (dist < min) min = dist;
		cur_ray = cur_ray->child;
	}

	return min;
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

void ray::set_emitter_radius(qreal r) {	emitter_radius = r; }

void ray::generate_outline()
{
	if (path) delete path;
	path = new QPainterPath;
	path->moveTo(emitter);
	if (intersection_point) path->lineTo(*intersection_point);
	else
	{
        vector2D ray_end(dir_vector * ray_prop::max_len + emitter);
		path->lineTo(ray_end);
	}
}
