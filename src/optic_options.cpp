#include "optic_options.h"
#include "field.h"
#include "abstractoptics.h"

optic_options::optic_options(field *backg) :
    QQuickWidget()
{
    if (backg != nullptr)
        setParent((QWidget*)backg->parent());

    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setClearColor(Qt::transparent);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

optic_options::~optic_options()
{
}
