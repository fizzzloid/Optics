#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QWidget>

class ray;
class abstract_optics;
class QPainter;
class QPaintEvent;
class QPointF;

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

	public slots:
		void recalc();
		void paintEvent(QPaintEvent *);
		void scale_change(qint32 sc_st);
		void corner_change(qreal x, qreal y);
		void scale_turn(qint32 increment);
		void corner_turn(qreal incx, qreal incy);

	private:
		QList<ray *> rays;
		QList<abstract_optics *> optics;

		QPointF corner;
		qint32 scale_step;
		qreal scale;
		QColor background_color;
		QColor rays_color;
		QPen *rays_pen;
		QPen *emitter_pen;
		QBrush *background_brush;

		static const qreal scale_base = 1.3;
};

#endif // FIELD_H
