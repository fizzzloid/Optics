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
	r(backg->get_ray_num(chg_r_num)),
	r_num(chg_r_num)
{
	ui->setupUi(this);

	initial_color = r->get_color();
	initial_dir = r->get_direction();

	connect(ui->angle_dial, SIGNAL(valueChanged(int)),
			this, SLOT(dial_changed(int)));
	connect(ui->angle_spinbox, SIGNAL(valueChanged(double)),
			this, SLOT(spin_box_changed(double)));

	connect(ui->red_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));
	connect(ui->green_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));
	connect(ui->blue_slider, SIGNAL(valueChanged(int)),
			this, SLOT(color_changed()));

	connect(ui->buttonBox, SIGNAL(rejected()),
			this, SLOT(cancel()));
	connect(ui->reset_btn, SIGNAL(clicked()),
			this, SLOT(restore_initials()));

	restore();

}

ray_options::~ray_options() { delete ui; }
void ray_options::spin_box_changed(double deg) { set_angle(deg); }

void ray_options::dial_changed(int deg)
{
	int ia = deg + 360 - 90;
	ia %= 360;
	set_angle(deg);
}

void ray_options::color_changed()
{
	set_color(ui->red_slider->value(),
			  ui->green_slider->value(),
			  ui->blue_slider->value());
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
	r->get_field()->recalc_ray_num(r_num);
}

void ray_options::restore()
{
	blockSignals(true);
	ui->red_slider->setValue(initial_color.red());
	ui->green_slider->setValue(initial_color.green());
	ui->blue_slider->setValue(initial_color.black());
	set_color(initial_color.red(),
			  initial_color.green(),
			  initial_color.blue());
	set_angle(qRadiansToDegrees(initial_dir));
	blockSignals(false);
	r->get_field()->recalc_ray_num(r_num);
}
