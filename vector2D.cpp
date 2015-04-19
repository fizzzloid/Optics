#include "vector2D.h"
#include <QtMath>

vector2D::vector2D(qreal xpos, qreal ypos) : QPointF(xpos, ypos) {}
vector2D::vector2D(QPointF p) : QPointF(p) {}


qreal vector2D::scalar_mult(vector2D p) const
{
	return ( x()*p.x() + y() * p.y() );
}


qreal vector2D::length() const
{ return qSqrt( x()*x() + y() * y() ); }

qreal vector2D::vect_mult(vector2D p) const
{
	return ( x()*p.y() - y()*p.x() );
}

qreal vector2D::distance(vector2D p) const
{
	p -= *this;
	return p.length();
}

vector2D vector2D::operator =(const vector2D &p)
{
	setX(p.x());
	setY(p.y());
	return *this;
}

qreal vector2D::angle() const
{
	vector2D ort = *this / length();
	qreal angle = qAsin(ort.y());
	if (ort.x() < 0) angle += M_PI;
	return qRadiansToDegrees(angle);
}
