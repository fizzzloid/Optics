#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QWidget>

class ray;
class abstract_optics;
class QPointF;
class QPainter;
class QPaintEvent;
class QKeyEvent;
class QEvent;
class QWheelEvent;

class field : public QWidget
{
		Q_OBJECT

	public:
		field(QWidget *parent = 0);
		~field();
		QList<ray *> get_rays() const;
		QList<abstract_optics *> get_optics() const;
		void add_ray(ray *r);
		void add_optic(abstract_optics *o);
		void delete_ray(ray *r);
		void delete_optic(abstract_optics *o);

		void clear();

		void recalc();
		void recalc_ray_num(qint32 n);
		void scale_change(qint32 new_sc, QPointF *center = 0);
		void corner_change(qreal x, qreal y);
		void scale_turn(qint32 increment, QPointF *center = 0);
		void corner_turn(qreal incx, qreal incy);
		void scaled_corner_turn(qreal incx, qreal incy);
		qreal get_scale() const;
		QPointF get_corner() const;

		void set_index_of_refraction(qreal i);
		qreal get_index_of_refraction() const;

		quint32 rays_count() const;

		void show_grid(bool show);

	public slots:
		void paintEvent(QPaintEvent *);
		void keyPressEvent(QKeyEvent *ke);
		void enterEvent(QEvent *);
		void leaveEvent(QEvent *);
		void wheelEvent(QWheelEvent *we);
		void mouseMoveEvent(QMouseEvent *me);
		void mousePressEvent(QMouseEvent *me);
		void mouseReleaseEvent(QMouseEvent *);

	signals:
		void something_changed();

	private:
		void paintRay(qint32 num, QPainter *painter);

		QList<ray *> rays;
		QList<abstract_optics *> optics;

		QPointF corner;
		qint32 scale_step;
		qreal scale;
		QColor background_color;
		QColor rays_color;
		QPen *rays_pen;
		QPen *emitter_pen;
		QBrush *emitter_brush;
		QBrush *background_brush;
		qreal index_of_refr;

		bool mouse_inside;
		QPoint mouse_click_pos;

		bool grid_visible;

		static const qreal scale_base = 1.3;
		static const qreal turn_koeff = 0.1;
};

#endif // FIELD_H
