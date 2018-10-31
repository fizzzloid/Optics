#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QWidget>
#include <QSet>
#include "optic_options.h"

class ray;
class abstract_optics;
class QPointF;
class QPainter;
class QPaintEvent;
class QKeyEvent;
class QEvent;
class QWheelEvent;
class QMenu;
class QContextMenuEvent;

class field : public QWidget
{
    Q_OBJECT

public:
    field(QWidget *parent = 0);
    ~field();

    QWidget* options()
    {
        return m_options;
    }

    QList<ray *> get_rays() const;
    QList<abstract_optics *> get_optics() const;

    void add_ray(ray *r);

    void add_optic(abstract_optics *o);

    void delete_ray(ray *r);

    void delete_optic(abstract_optics *o);

    ray *get_ray_num(qint32 num) const;

    abstract_optics *get_optic_num(qint32 num) const;

    void clear();

    void recalc();

    void recalc_ray_num(qint32 n);

    void scale_change(qint32 new_sc, QPointF *center = 0);

    void corner_change(qreal x, qreal y);

    void scale_turn(qint32 increment, QPointF *center = 0);

    void corner_turn(qreal incx, qreal incy);

    void scaled_corner_turn(qreal incx, qreal incy);

    qreal get_scale() const;

    QPointF get_corner() const;

    void set_index_of_refraction(qreal i);

    qreal get_index_of_refraction() const;

    QSet<qint32> get_highlited_rays() const;

    QSet<qint32> get_highlited_optics() const;

    QString who_is_optic(qint32 num) const;

    quint32 rays_count() const;

    void show_grid(bool show);

    void find_focalpoint();

public slots:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ke);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void wheelEvent(QWheelEvent *we);

    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *);

    void highlight_ray(qint32 num);
    void highlight_optic(qint32 num);

signals:
    void something_changed();

private:
    void paintRay(qint32 num, QPainter *painter, bool selected) const;
    void paintOptic(qint32 num, QPainter *painter, bool selected) const;
    void paintGrid(QPainter *painter) const;

    bool highlight_changed();
    QList<ray *> rays;
    QList<abstract_optics *> optics;
    QVector<QPointF> ray_path;

    QPointF corner;
    qint32 scale_step;
    qreal scale;
    QColor background_color;
    QColor rays_color;
    QPen *rays_pen = nullptr;
    QPen *emitter_pen = nullptr;
    QBrush *emitter_brush = nullptr;
    QBrush *background_brush = nullptr;
    qreal index_of_refr;
    optic_options* m_options = nullptr;

    bool mouse_inside;
    QPoint mouse_click_pos;
    QSet<qint32> highlighted_rays;
    QSet<qint32> highlighted_optics;
    bool grid_visible;
    bool m_startcollect = false;
    bool m_startpaint = false;

    const qreal scale_base = 1.3;
    const qreal turn_koeff = 0.1;
    const qint32 mouse_select_distance = 5;

};

#endif // FIELD_H
