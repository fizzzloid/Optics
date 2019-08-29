#ifndef ABSTRACTOPTICS_H
#define ABSTRACTOPTICS_H

#include <QList>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QPair>
class vector2D;
class ray;
class field;
class QString;

class abstract_optics : public QObject
{
public:
    abstract_optics(field *backg);
    virtual ~abstract_optics();

    virtual QPair<vector2D *, qint32> intersection_with_ray(ray *) const;
    virtual ray *generate_ray(ray *);

    QPainterPath get_outline() const;
    QPen get_pen() const;
    QBrush get_brush () const;

    virtual qreal get_distance_to_point(vector2D) const;
    virtual void setup_pen_and_brush();
    virtual void set_pen_color(QColor c);
    virtual void set_brush_color(QColor c);

    virtual void move_to(qreal, qreal);
    virtual void move_by(qreal, qreal);
    virtual void rot_by(qreal a);
    virtual void set_angle(qreal a);
    virtual void set_nodal_points(QList<vector2D>);

    virtual qreal get_angle() const;
    virtual QList<vector2D> get_nodal_points() const;

    virtual QString who_i_am() const;
    virtual QString get_position() const;

protected:
    field *background;
    QPainterPath outline;
    QPen pen;
    QBrush brush;

    qreal m_angle = 0.0;
    virtual void generate_outline();
};

#endif // ABSTRACTOPTICS_H
