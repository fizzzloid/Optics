#include "optic_options.h"
#include "field.h"
#include "abstractoptics.h"

optic_options::optic_options(field *backg) :
    QQuickWidget(0),
    background(backg)
{
}

optic_options::~optic_options()
{
}
