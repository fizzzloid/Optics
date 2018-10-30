#ifndef REAL_LENSE_H
#define REAL_LENSE_H

#include "abstractoptics.h"
#include "vector2D.h"
#include <QPair>
class ray;
class field;
class QString;

class real_lense : public abstract_optics
{
public:
    real_lense(vector2D a, vector2D b,
               qreal thicknes,
               qreal radius1, qreal radius2,
               qreal index_of_refraction, field *backg);
    ~real_lense();

    void update_pose();

    QPair<vector2D *, qint32> intersection_with_ray(ray *) const;
    ray *generate_ray(ray *);

    qreal get_distance_to_point(vector2D p) const;

    QString who_i_am() const;

    void rot_by(qreal a);

    void move_by(qreal, qreal);

private:
    void generate_outline();

    qreal radius1, radius2;
    qreal thick, R1, R2, index_of_refr, length, angle1, angle2;

    vector2D edge_a, edge_b, center1, center2,
             normal, tangent, center0,
             angle_v_1a, angle_v_1b, angle_v_2a, angle_v_2b,
             corner_1a, corner_1b, corner_2a, corner_2b;
};

#endif // REAL_LENSE_H
