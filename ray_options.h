#ifndef RAY_OPTIONS_H
#define RAY_OPTIONS_H

#include <QDialog>
#include <QColor>
class ray;
class field;

namespace Ui {
class ray_options;
}

class ray_options : public QDialog
{
		Q_OBJECT

	public:
		explicit ray_options(qint32 chg_r_num, field *backg,
							 QWidget *parent = 0);
		~ray_options();

	private slots:
		void spin_box_changed(double deg);
		void dial_changed(int deg);
		void color_changed();
		void restore_initials();
		void cancel();

	private:
		void set_color(qint32 red, qint32 green, qint32 blue);
		void set_angle(qreal deg);
		void restore();

		Ui::ray_options *ui;
		QColor initial_color;
		qreal initial_dir;
		ray *r;
		qint32 r_num;
};

#endif // RAY_OPTIONS_H
