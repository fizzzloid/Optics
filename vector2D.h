#ifndef vector2D_H
#define vector2D_H

#include <QPointF>
class vector2D : public QPointF
{
	public:
		vector2D(qreal xpos = 0.0, qreal ypos = 0.0);
		vector2D(QPointF p);
		qreal length() const;
		qreal distance(vector2D p) const;
		qreal scalar_mult(vector2D p) const ;
		qreal vect_mult(vector2D p) const;
		vector2D operator= (const vector2D &p);
};

#endif // vector2D_H
