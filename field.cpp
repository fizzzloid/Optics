#include "field.h"
#include "ray.h"
#include "lenses.h"
#include <QPainter>
#include <QKeyEvent>
#include <QtMath>
#include <QDebug>

field::field(QWidget *parent) : QWidget(parent)
{
	corner = QPointF(0,0);
	scale_step = 0;
	scale = 1000.0;

	index_of_refr = 1.0;

	background_color = Qt::black;
	rays_color = Qt::red;
	background_brush = new QBrush(background_color, Qt::SolidPattern);
	rays_pen = new QPen(rays_color, 1.0, Qt::SolidLine);
	emitter_pen = new QPen(rays_color, 2.0, Qt::SolidLine);
	emitter_brush = new QBrush(rays_color, Qt::SolidPattern);

	setMouseTracking(true);
	mouse_inside = false;
	grid_visible = true;

	emit something_changed();
}

field::~field() { clear(); }
QList<ray *> field::get_rays() const { return rays; }
QList<abstract_optics *> field::get_optics() const { return optics; }

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

void field::delete_ray(ray *r) { rays.removeOne(r); }
void field::delete_optic(abstract_optics *o) { optics.removeOne(o); }

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
		recalc_ray_num(i);
}

void field::recalc_ray_num(qint32 n)
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

void field::scale_change(qint32 new_sc, QPointF *center)
{
	qreal old_sc = scale;

	if (!center)
	{
		center = new QPointF;
		center->setX(corner.x() + width() / (2 * scale));
		center->setY(corner.y() + height() / (2 * scale));
	}
	scale_step = new_sc;
	scale = 1000*qPow(scale_base, (qreal) new_sc);

	QPointF new_corner( *center
						+ (corner - *center) * old_sc / scale);
	corner_change(new_corner.x(), new_corner.y());

}

void field::corner_change(qreal x, qreal y)
{
	corner.setX(x);
	corner.setY(y);
}

void field::scale_turn(qint32 increment, QPointF *center)
{
	scale_change(scale_step + increment, center);
}

void field::corner_turn(qreal incx, qreal incy)
{
	corner.setX(corner.x() + incx);
	corner.setY(corner.y() + incy);
}

void field::scaled_corner_turn(qreal incx, qreal incy)
{
	corner_turn(incx / scale, incy / scale);
}

qreal field::get_scale() const { return scale; }
QPointF field::get_corner() const {	return corner; }

void field::set_index_of_refraction(qreal i)
{
	index_of_refr = i;
	recalc();
}

qreal field::get_index_of_refraction() const { return index_of_refr; }

quint32 field::rays_count() const
{
	qint32 l = rays.length();
	qint32 i = 0;
	quint32 result = 0;
	bool f = (i < l);
	ray *cur_ray;
	if (f) cur_ray = rays[0];
	while (f)
	{
		result++;
		cur_ray = cur_ray->get_child();
		if (!cur_ray)
			if (f = (++i) < l) cur_ray = rays[i];
	}

	return result;
}

void field::show_grid(bool show)
{
	if (show != grid_visible)
	{
		grid_visible = show;
		update(); emit something_changed();
	}

}

void field::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(0, 0, width(), height(), *background_brush);

	painter.translate(-corner.x()*scale, corner.y()*scale + height());
	painter.scale(scale, -scale);

	// grid
	if (grid_visible)
	{

		static const qreal ln_10 = 2.302585092994046;
		qreal lines_dist =  qPow(10.0, 2 - (qint32) (qLn(scale)/ln_10));
		qint32 h_lines_count = 2 + height() / (scale * lines_dist);
		qreal first_line_y = ( (int) (corner.y() / lines_dist) - 1)
				* lines_dist;
		qint32 v_lines_count = 2 + width() / (scale * lines_dist);
		qreal first_line_x = ( (int) (corner.x() / lines_dist) - 1)
				* lines_dist;

		QColor grid_color;
		grid_color.setRgb(32,32,32);
		painter.setPen(QPen(grid_color, 0, Qt::SolidLine));
		for (qint32 i = 0; i < h_lines_count * 5; i++)
		{
			qreal y = first_line_y + i * lines_dist * 0.2;
			painter.drawLine(QPointF(corner.x(), y),
							 QPointF(corner.x() + width() / scale, y));
		}

		painter.setPen(QPen(grid_color, 0, Qt::SolidLine));
		for (qint32 i = 0; i < v_lines_count * 5; i++)
		{
			qreal x = first_line_x + i * lines_dist * 0.2;
			painter.drawLine(QPointF(x, corner.y()),
							 QPointF(x, corner.y() + height() / scale));
		}

		grid_color.setRgb(150, 150, 150);
		painter.setPen(QPen(grid_color, 2/scale, Qt::SolidLine));
		for (qint32 i = 0; i < h_lines_count; i++)
		{
			qreal y = first_line_y + i * lines_dist;
			painter.drawLine(QPointF(corner.x(), y),
							 QPointF(corner.x() + width() / scale, y));
		}

		for (qint32 i = 0; i < v_lines_count; i++)
		{
			qreal x = first_line_x + i * lines_dist;
			painter.drawLine(QPointF(x, corner.y()),
							 QPointF(x, corner.y() + height() / scale));
		}
	}

	// rays
	qint32 l = rays.length();
	for (qint32 i = 0; i < l; i++)
		paintRay(i, &painter, selected_rays.contains(i));


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

void field::keyPressEvent(QKeyEvent *ke)
{
	switch (ke->key())
	{
	case Qt::Key_Up:
		scaled_corner_turn(0, height() * turn_koeff);
		update(); emit something_changed();
		break;

	case Qt::Key_Down:
		scaled_corner_turn(0, -height() * turn_koeff);
		update(); emit something_changed();
		break;
	case Qt::Key_Left:
		scaled_corner_turn(-width() * turn_koeff, 0);
		update(); emit something_changed();
		break;
	case Qt::Key_Right:
		scaled_corner_turn(width() * turn_koeff, 0);
		update(); emit something_changed();
		break;

	case Qt::Key_Equal:
	case Qt::Key_Plus:
		scale_turn(1.0);
		update(); emit something_changed();
		break;
	case Qt::Key_Minus:
		scale_turn(-1.0);
		update(); emit something_changed();
		break;

	default:
		break;
	}

}

void field::enterEvent(QEvent *) { mouse_inside = true; }
void field::leaveEvent(QEvent *) { mouse_inside = false; }

void field::wheelEvent(QWheelEvent *we)
{
	QPointF *center = new QPointF;
	center->setX(corner.x() + we->x() / scale);
	center->setY(corner.y() + (height() - we->y()) / scale);
	scale_turn(0.01*we->delta(), center);
	update(); emit something_changed();
}

void field::mouseMoveEvent(QMouseEvent *me)
{
	QPointF delta;
	delta.setX( me->x() - mouse_click_pos.x() );
	delta.setY( me->y() - mouse_click_pos.y() );
	delta /= scale;
	switch (me->buttons())
	{
	case Qt::LeftButton:
		corner_turn(- delta.x(), delta.y());
		update(); emit something_changed();
		break;

	default:
		vector2D mouse_pos;
		mouse_pos.setX(corner.x() + mouse_click_pos.x() / scale);
		mouse_pos.setY(corner.y() +
					   (height() - mouse_click_pos.y()) / scale);
		bool selection_changed = false;
		qint32 l = rays.length();
		for (qint32 i = 0; i < l; i++)
		{
			bool flag1 =
					rays[i]->get_distance_to_point(mouse_pos) * scale
					<= mouse_select_distance;
			bool flag2 = selected_rays.contains(i);
			if (flag1 != flag2)
			{
				selection_changed = true;
				if (flag1) selected_rays.insert(i);
				else selected_rays.remove(i);
			}
		}
		if (selection_changed) update();
		break;
	}

	mouse_click_pos.setX(me->x());
	mouse_click_pos.setY(me->y());
}

void field::mousePressEvent(QMouseEvent *me)
{
	mouse_click_pos.setX(me->x());
	mouse_click_pos.setY(me->y());
	 if (me->buttons() & Qt::LeftButton)
		 setCursor(Qt::ClosedHandCursor);
}

void field::mouseReleaseEvent(QMouseEvent *)
{
	unsetCursor();
}

void field::paintRay(qint32 num, QPainter *painter, bool selected)
{
	ray *cur_ray = rays[num];
	while (cur_ray)
	{
		if (!cur_ray->get_parent())
		{
			QPen e_pen = cur_ray->get_emitter_pen();
			qreal r = cur_ray->get_emitter_radius() / scale;
			e_pen.setWidthF(e_pen.widthF()/scale);
			painter->setBrush(cur_ray->get_emitter_brush());
			painter->setPen(e_pen);
			painter->drawEllipse(cur_ray->get_emitter_pos(),r, r);
		}

		QPen r_pen = cur_ray->get_pen();
		if (selected)
			r_pen.setWidthF(2 * (1 + r_pen.widthF())/scale);
		else r_pen.setWidthF(r_pen.widthF()/scale);
		painter->setPen(r_pen);
		painter->drawPath(cur_ray->get_path());

		cur_ray = cur_ray->get_child();
	}

}
