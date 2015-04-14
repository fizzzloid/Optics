#include "position.h"
#include <QtMath>

position::position(qreal xpos, qreal ypos) : QPointF(xpos, ypos) {}

qreal position::scalar_mult(position p)
{
	return ( x()*p.x() + y() * p.y() ) / mm_in_m / mm_in_m;
}


qreal position::length() const
{ return qSqrt( x()*x() + y() * y() ) / mm_in_m; }

qreal position::distance(position p) const
{
	position l = *this;
	l-=p;
	return l.length();
}
