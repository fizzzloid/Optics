#ifndef RAY_H
#define RAY_H

#include "vector2D.h"
#include <QPainterPath>
#include <QPen>
class abstract_optics;
class field;


class ray
{
	public:
		ray(qreal xpos, qreal ypos, qreal dir, field *f, qreal intens = 1.0);
		ray(qreal xpos, qreal ypos, vector2D dir_v, field *f, qreal intens = 1.0);
		~ray();

		vector2D get_emitter_pos() const;
		qreal get_direction() const;
		vector2D get_direction_vect() const;
		qreal get_intensity() const;

		void set_intensity(qreal intens);
		void set_direction(qreal dir);
		void set_direction_vect(vector2D dir_vect);
		void set_emitter_pos(vector2D emitter_pos);

		ray *get_parent() const;
		ray *get_child() const;

		void set_child(ray *r);

		field *get_field() const;

		bool new_intersecting_object();
		abstract_optics *get_intersection_object() const;
		vector2D *get_intersection_point() const;
		qint32 get_intersection_part() const;

		abstract_optics *get_generator() const;
		void set_generator(abstract_optics *o);

		QColor get_color() const;
		QPen get_pen() const;
		QPen get_emitter_pen() const;
		QBrush get_emitter_brush() const;
		QPainterPath get_path() const;
		qreal get_emitter_radius() const;

		void set_color(QColor c);
		void set_pen(QPen p);
		void set_emitter_brush(QBrush b);
		void set_emitter_pen(QPen p);
		void setup_colors();
		void set_emitter_radius(qreal r);

		qreal get_distance_to_point(vector2D p) const ;

		const static qreal max_len = 1e3;
		const static qreal min_intensity = 0.01;
		const static qreal intensity_step = 0.01;

	private:
		void generate_outline();

		vector2D emitter;
		vector2D dir_vector;
		qreal direction;
		qreal intensity;

		ray *parent;
		ray *child;

		abstract_optics *intersection_object;
		vector2D *intersection_point;
		qint32 intersection_part;

		abstract_optics *generator;
		field *background;

		QColor color;
		QPen pen;
		QPen emitter_pen;
		QBrush emitter_brush;
		QPainterPath *path;
		qreal emitter_radius;
};

#endif // RAY_H
