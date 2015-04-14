#include "field.h"
#include "ray.h"
#include "linses.h"
#include <QPainter>
#include <QtMath>

field::field(QWidget *parent) : QWidget(parent)
{
	corner = QPointF(0,0);
	scale_step = 0;
	scale = 1.0;

	background_color = Qt::white;
	rays_color = Qt::red;
	background_brush = new QBrush(background_color, Qt::SolidPattern);
	rays_pen = new QPen(rays_color, 2, Qt::SolidLine);
	emitter_pen = new QPen(rays_color, 4);
}

field::~field()
{
	clear();
}

inline QList<ray *> field::get_rays() const
{ return rays; }

QList<abstract_optics *> field::get_optics() const
{ return optics; }

void field::add_ray(ray *r)
{
	if (r && (rays.indexOf(r) == -1))
	{
		rays.append(r);
		recalc();
	}
}

void field::add_optic(abstract_optics *o)
{
	if (o && (optics.indexOf(o) == -1))
	{
		optics.append(o);
		recalc();
	}
}

void field::delete_ray(ray *r)
{
	rays.removeOne(r);
	delete r;
}

void field::delete_optic(abstract_optics *o)
{
	optics.removeOne(o);
	delete o;
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

void field::recalc()	// need to be optimized
{
	ray *cur_ray = 0;
	for (qint32 i = 0; i < rays.length(); i++)
	{
		cur_ray = rays[i];
		if (cur_ray->new_intersecting_object())
		{
			cur_ray->set_child(0);
			ray *new_ray = cur_ray->get_intersection_object()
					->generate_ray(cur_ray);
			add_ray(new_ray);
		}
	}
}

void field::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(0, 0, width(), height(), *background_brush);

	painter.translate(corner.x(), corner.y() + height());
	painter.scale(scale, -scale);

	// optics
	quint32 l = optics.length();
	for (quint32 i = 0; i < l; i++)
	{
		abstract_optics *cur_opt = optics[i];
		painter.setPen(cur_opt->get_pen());
		painter.setBrush(cur_opt->get_brush());
		painter.drawPath(cur_opt->get_outline());
	}

	// rays
	l = rays.length();
	for (quint32 i = 0; i < l; i++)
	{
		ray *cur_ray = rays[i];

		QPointF ray_start = cur_ray->get_emitter_pos();
		ray_start += corner;

		QPointF ray_end;
		if (cur_ray->get_intersection_point())
			ray_end = *(cur_ray->get_intersection_point());
		else
		{
			ray_end = QPointF(qCos(cur_ray->get_direction()),
							  qSin(cur_ray->get_direction()));
			ray_end *= ray::max_len;
			ray_end += cur_ray->get_emitter_pos();
		}
		ray_end += corner;

		painter.setPen(*emitter_pen);
		painter.drawPoint(ray_start);
		painter.setPen(*rays_pen);
		painter.drawLine(ray_start, ray_end);
	}
}

void field::scale_change(qint32 sc_st)
{
	scale_step = sc_st;
	scale = qPow(scale_base, (qreal) sc_st);
}

void field::corner_change(qreal x, qreal y)
{
	corner.setX(x);
	corner.setY(y);
}

void field::scale_turn(qint32 increment)
{
	scale += increment;
}

void field::corner_turn(qreal incx, qreal incy)
{
	corner.rx() += incx;
	corner.ry() += incy;
}
