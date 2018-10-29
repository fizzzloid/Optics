#include "ray_options.h"
#include "ui_ray_options.h"
#include "ray.h"
#include "field.h"
#include <QPalette>
#include <QtMath>

ray_options::ray_options(qint32 chg_r_num, field *backg,
						 QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ray_options),
	backgroung(backg),
	r(backg->get_ray_num(chg_r_num)),
	r_num(chg_r_num)
{
	ui->setupUi(this);

	initial_color = r->get_color();
	initial_dir = r->get_direction();
	initial_pos = r->get_emitter_pos();

	connect(ui->angle_dial, SIGNAL(valueChanged(int)),
			this, SLOT(dial_changed(int)));
	connect(ui->angle_spinbox, SIGNAL(valueChanged(double)),
			this, SLOT(spin_box_changed(double)));
	connect(ui->ccv_btn, SIGNAL(clicked(bool)),
			ui->angle_spinbox, SLOT(stepUp()));
	connect(ui->cv_btn, SIGNAL(clicked(bool)),
			ui->angle_spinbox, SLOT(stepDown()));

	connect(ui->red_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));
	connect(ui->green_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));
	connect(ui->blue_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));

	connect(ui->x_spin_box, SIGNAL(valueChanged(double)),
			this, SLOT(pos_changed()));
	connect(ui->y_spin_box, SIGNAL(valueChanged(double)),
			this, SLOT(pos_changed()));
	connect(ui->up_btn, SIGNAL(clicked(bool)),
			this, SLOT(up_btn_click()));
	connect(ui->down_btn, SIGNAL(clicked(bool)),
			this, SLOT(down_btn_click()));
	connect(ui->left_btn, SIGNAL(clicked(bool)),
			this, SLOT(left_btn_click()));
	connect(ui->right_btn, SIGNAL(clicked(bool)),
			this, SLOT(right_btn_click()));

	connect(ui->buttonBox, SIGNAL(rejected()),
			this, SLOT(cancel()));
	connect(ui->reset_btn, SIGNAL(clicked()),
			this, SLOT(restore_initials()));
	connect(ui->delete_button, SIGNAL(clicked(bool)),
			this, SLOT(delete_btn_click()));

	restore();
}

ray_options::~ray_options() { delete ui; }

void ray_options::spin_box_changed(double deg)
{
	if (deg < 0.0) deg += 360;
	else if (deg >= 360) deg -= 360;
	set_angle(deg);
}

void ray_options::dial_changed(int deg)
{
	int ia = (deg + 360 - 90) % 360;
	set_angle(ia);
}

void ray_options::up_btn_click()
{
	qreal scale = backgroung->get_scale();
	qreal y = ui->y_spin_box->value();
	ui->y_spin_box->setValue(y + 10 / scale);
}

void ray_options::down_btn_click()
{
	qreal scale = backgroung->get_scale();
	qreal y = ui->y_spin_box->value();
	ui->y_spin_box->setValue(y - 10 / scale);
}

void ray_options::left_btn_click()
{
	qreal scale = backgroung->get_scale();
	qreal x = ui->x_spin_box->value();
	ui->x_spin_box->setValue(x - 10 / scale);
}

void ray_options::right_btn_click()
{
	qreal scale = backgroung->get_scale();
	qreal x = ui->x_spin_box->value();
	ui->x_spin_box->setValue(x + 10 / scale);
}

void ray_options::pos_changed()
{
	set_pos(ui->x_spin_box->value(),
			ui->y_spin_box->value());
}

void ray_options::color_changed()
{
	set_color(ui->red_slider->value(),
			  ui->green_slider->value(),
			  ui->blue_slider->value());
}

void ray_options::delete_btn_click()
{
	backgroung->delete_ray(r);
	delete r;
	emit accept();
}

void ray_options::restore_initials() { restore(); }
void ray_options::cancel()
{
	restore();
	emit reject();
}

void ray_options::set_color(qint32 red, qint32 green, qint32 blue)
{
	QLabel *l = ui->color_preview;
	QColor col(red, green, blue);
	QPalette pal = l->palette();
	pal.setColor(l->backgroundRole(), col);
	l->setPalette(pal);
	r->set_color(col);
	backgroung->update();
}

void ray_options::set_angle(qreal deg)
{
	ui->angle_dial->blockSignals(true);
	ui->angle_spinbox->blockSignals(true);

	ui->angle_dial->setValue( (((int) deg) + 90) % 360 );
	ui->angle_spinbox->setValue(deg);

	ui->angle_dial->blockSignals(false);
	ui->angle_spinbox->blockSignals(false);

	r->set_direction(qDegreesToRadians(deg));
	backgroung->recalc_ray_num(r_num);
	backgroung->update();
}

void ray_options::set_pos(qreal x, qreal y)
{
	r->set_emitter_pos(vector2D(x, y));
	backgroung->recalc_ray_num(r_num);
	backgroung->update();
}

void ray_options::restore()
{
	blockSignals(true);
	ui->red_slider->setValue(initial_color.red());
	ui->green_slider->setValue(initial_color.green());
	ui->blue_slider->setValue(initial_color.blue());
	ui->x_spin_box->setValue(initial_pos.x());
	ui->y_spin_box->setValue(initial_pos.y());
	set_color(initial_color.red(),
			  initial_color.green(),
			  initial_color.blue());
	set_angle(qRadiansToDegrees(initial_dir));
	set_pos(initial_pos.x(), initial_pos.y());
	blockSignals(false);
}
