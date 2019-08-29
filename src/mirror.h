#ifndef MIRROR_H
#define MIRROR_H

#include <abstractoptics.h>
#include "vector2D.h"
#include <QPair>
class QString;

class mirror : public abstract_optics
{
public:
    mirror(vector2D start, vector2D end, bool orient,  field *backg);
    ~mirror();

    void update_pose();

    QPair<vector2D *, qint32> intersection_with_ray(ray *r) const;

    ray *generate_ray(ray *r);

    qreal get_distance_to_point(vector2D p) const;

    QString who_i_am() const;

    void rot_by(qreal a);

    void move_by(qreal, qreal);

    static const quint32 hatch_count = 15;

    QString get_position() const;
private:
    vector2D edge_a, edge_b, normal, tangent;
    qreal length;
    bool m_orient;

    void generate_outline();
};

#endif // MIRROR_H
