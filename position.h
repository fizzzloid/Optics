#ifndef POSITION_H
#define POSITION_H

#include <QPointF>
class position : public QPointF
{
	public:
		position(qreal xpos = 0.0, qreal ypos = 0.0);
		qreal length() const;
		qreal distance(position p) const;
		qreal scalar_mult(position p) const ;
		qreal vect_mult(position p) const;
};

#endif // POSITION_H
