#ifndef OPTIC_OPTIONS_H
#define OPTIC_OPTIONS_H

#include <QDialog>
#include <QColor>
#include <QList>
#include "vector2D.h"
class abstract_optics;
class field;

namespace Ui {
class optic_options;
}

class optic_options : public QDialog
{
		Q_OBJECT

	public:
		explicit optic_options(qint32 chg_opt_num,
							   field *backg,
							   QWidget *parent = 0);
		~optic_options();

	private slots:
		void angle_dial_changed(int deg);
		void angle_spin_changed(qreal deg);
		void up_btn_clicked();
		void down_btn_clicked();
		void left_btn_clicked();
		void right_btn_clicked();
		void pos_changed();
		void outline_color_click();
		void material_color_click();
		void outline_color_changed(QColor c);
		void outline_opacy_changed(double o);
		void material_color_changed(QColor c);
		void material_opacy_changed(double o);
		void delete_btn_click();
		void reset();
		void cancel();

	private:
		void restore();
		void set_outline_color(QColor c);
		void set_material_color(QColor c);
		void set_pos(qreal x, qreal y);
		void move_pos(qreal inc_x, qreal inc_y);
		void set_angle(qreal deg);

		void connect_angle();
		void connect_movement();
		void connect_colors();
		void connect_buttons();

		Ui::optic_options *ui;
		QColor initial_outline_color, current_outline_color;
		QColor initial_material_color, current_material_color;
		QList<vector2D> initial_nodal_points;
		QList<vector2D> current_nodal_points;
		vector2D initial_pos;
		vector2D current_pos;
		qreal initial_angle;
		abstract_optics *opt;
		field *background;
		qint32 opt_num;
};

#endif // OPTIC_OPTIONS_H
