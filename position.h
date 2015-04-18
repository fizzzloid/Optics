#ifndef POSITION_H
#define POSITION_H

#include <QPointF>
class position : public QPointF
{
	public:
		position(qreal xpos = 0.0, qreal ypos = 0.0);
		position(QPointF p);
		qreal length() const;
		qreal distance(position p) const;
		qreal scalar_mult(position p) const ;
		qreal vect_mult(position p) const;
		position operator= (position p);
};

#endif // POSITION_H
