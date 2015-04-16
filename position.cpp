#include "position.h"
#include <QtMath>

position::position(qreal xpos, qreal ypos) : QPointF(xpos, ypos) {}
position::position(QPointF p) : QPointF(p) {}


qreal position::scalar_mult(position p) const
{
	return ( x()*p.x() + y() * p.y() );
}


qreal position::length() const
{ return qSqrt( x()*x() + y() * y() ); }

qreal position::vect_mult(position p) const
{
	return ( x()*p.y() - y()*p.x() );
}

qreal position::distance(position p) const
{
	p -= *this;
	return p.length();
}
