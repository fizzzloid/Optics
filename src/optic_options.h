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
public:
    explicit optic_options(field *backg);
    ~optic_options();

private:
    field *background;
};

#endif // OPTIC_OPTIONS_H
