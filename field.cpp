#include "field.h"
#include "ray.h"
#include "lenses.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

field::field(QWidget *parent) : QWidget(parent)
{
	corner = QPointF(0,0);
	scale_step = 0;
	scale = 1000.0;

	background_color = Qt::black;
	rays_color = Qt::red;
	background_brush = new QBrush(background_color, Qt::SolidPattern);
	rays_pen = new QPen(rays_color, 1.0, Qt::SolidLine);
	emitter_pen = new QPen(rays_color, 2.0, Qt::SolidLine);
	emitter_brush = new QBrush(rays_color, Qt::SolidPattern);
}

field::~field()
{
	clear();
}

QList<ray *> field::get_rays() const
{ return rays; }

QList<abstract_optics *> field::get_optics() const
{ return optics; }

void field::add_ray(ray *r)
{
	if (r && (rays.indexOf(r) == -1))
		rays.append(r);
}

void field::add_optic(abstract_optics *o)
{
	if (o && (optics.indexOf(o) == -1))
		optics.append(o);
}

void field::delete_ray(ray *r)
{
	rays.removeOne(r);
}

void field::delete_optic(abstract_optics *o)
{
	optics.removeOne(o);
}

void field::clear()
{
	for (quint32 i = rays.length(); i > 0; i--)
	{
		delete rays.first();
		rays.removeFirst();
	}

	for (quint32 i = optics.length(); i > 0; i--)
	{
		delete optics.first();
		optics.removeFirst();
	}

}

void field::recalc()
{
	qint32 l = rays.length();
	for (qint32 i = 0; i < l; i++)
		recalc_ray_on(i);
}

void field::recalc_ray_on(qint32 n)
{
	if (n >= rays.length()) return;

	ray *cur_ray = rays[n];
	while (cur_ray)
	{

		if (cur_ray->new_intersecting_object()
			&& cur_ray->get_intersection_object())
		{
			abstract_optics *int_opt =
					cur_ray->get_intersection_object();
			int_opt->generate_ray(cur_ray);
		}
		cur_ray = cur_ray->get_child();
	}
}

void field::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(0, 0, width(), height(), *background_brush);

	painter.translate(-corner.x()*scale, corner.y()*scale + height());
	painter.scale(scale, -scale);

	// rays
	qint32 l = rays.length();
	qint32 i = 0;
	bool f = i < l;
	ray *cur_ray;
	if (f) cur_ray = rays[i];
	while (f)
	{
		if (!cur_ray->get_parent())
		{
			QPen e_pen = cur_ray->get_emitter_pen();
			qreal r = cur_ray->get_emitter_radius() / scale;
			e_pen.setWidthF(e_pen.widthF()/scale);
			painter.setBrush(cur_ray->get_emitter_brush());
			painter.setPen(e_pen);
			painter.drawEllipse(cur_ray->get_emitter_pos(),r, r);
		}
		QPen r_pen = cur_ray->get_pen();
		r_pen.setWidthF(r_pen.widthF()/scale);
		painter.setPen(r_pen);
		painter.drawPath(cur_ray->get_path());

		if (cur_ray->get_child()) cur_ray = cur_ray->get_child();
		else
		{
			f = ++i < l;
			if (f) cur_ray = rays[i];
		}
	}

	// optics
	l = optics.length();
	for (qint32 i = 0; i < l; i++)
	{
		abstract_optics *cur_opt = optics[i];
		QPen o_pen = cur_opt->get_pen();
		o_pen.setWidthF(o_pen.widthF()/scale);
		painter.setPen(o_pen);
		painter.setBrush(cur_opt->get_brush());
		painter.drawPath(cur_opt->get_outline());
	}
}

void field::scale_change(qint32 sc_st)
{
	scale_step = sc_st;
	scale = 1000*qPow(scale_base, (qreal) sc_st);
}

void field::corner_change(qreal x, qreal y)
{
	corner.setX(x);
	corner.setY(y);
}

void field::scale_turn(qint32 increment)
{
	scale_change(scale_step + increment);
}

void field::corner_turn(qreal incx, qreal incy)
{
	corner.setX(corner.x() + incx);
	corner.setY(corner.y() + incy);
}
