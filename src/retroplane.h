#ifndef RETROPLANE_H
#define RETROPLANE_H

#include <abstractoptics.h>
#include "vector2D.h"
#include <QPair>
class QString;

class retroplane : public abstract_optics
{
public:
    retroplane(vector2D start, vector2D end, bool orient,  field *backg);

    void update_pose();

    QPair<vector2D *, qint32>intersection_with_ray(ray *r) const;

    ray *generate_ray(ray *r);

    qreal get_distance_to_point(vector2D p) const;

    QString who_i_am() const;

    void rot_by(qreal a);

    void move_by(qreal, qreal);

    static const quint32 hatch_count = 6;

private:
    vector2D edge_a, edge_b, normal, tangent;
    qreal length;
    bool m_orient;

    void generate_outline();
};

#endif // RETROPLANE_H
