#ifndef OPTIC_OPTIONS_H
#define OPTIC_OPTIONS_H

#include <QQuickWidget>
#include <QColor>
#include <QList>
#include "vector2D.h"
class abstract_optics;
class field;

namespace Ui {
class optic_options;
}

class optic_options : public QQuickWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal focallength READ focallength WRITE setFocallength)
    Q_PROPERTY(qreal height READ height WRITE setHeight)
    Q_PROPERTY(qreal distance3 READ distance3 WRITE setDistance3)
public:
    explicit optic_options(field *backg);
    ~optic_options();

    void setFocallength(qreal v)
    {
        m_focallength = v;
        emit sgnFocalLength(v);
    }

    void setHeight(qreal h)
    {
        m_height = h;
        emit sgnHeight(h);
    }

    void setDistance3(qreal d)
    {
        m_distance3 = d;
        emit sgnDistance3(d);
    }

    qreal height() const
    {
        return m_height;
    }

    qreal focallength() const
    {
        return m_focallength;
    }

    qreal distance3() const
    {
        return m_distance3;
    }

signals:
    void sgnDistance3(qreal);
    void sgnHeight(qreal);
    void sgnFocalLength(qreal);

private:
    field *background;
    qreal m_focallength;
    qreal m_distance3;
    qreal m_height;
};

#endif // OPTIC_OPTIONS_H
