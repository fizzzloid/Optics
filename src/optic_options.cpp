#include "optic_options.h"
#include "ui_optic_options.h"
#include "field.h"
#include "abstractoptics.h"
#include <QColorDialog>
#include <QtMath>
optic_options::optic_options(qint32 chg_opt_num,
							 field *backg,
							 QWidget *parent) :
	QDialog(parent),
	ui(new Ui::optic_options),
	background(backg),
	opt_num(chg_opt_num),
	opt(backg->get_optic_num(chg_opt_num))
{
	ui->setupUi(this);

	initial_angle = opt->get_angle();
	initial_material_color = opt->get_brush().color();
	initial_outline_color = opt->get_pen().color();
	initial_nodal_points = opt->get_nodal_points();
	qint32 l = initial_nodal_points.length();
	initial_pos = vector2D(0,0);
	for (qint32 i = 0; i < l; i++)
		initial_pos += initial_nodal_points[i];
	initial_pos /= l;

	connect_angle();
	connect_movement();
	connect_colors();
	connect_buttons();

	restore();
}

optic_options::~optic_options() { delete ui; }

void optic_options::angle_dial_changed(int deg)
{
	int ia = (deg + 360 - 90) % 360;
	set_angle(ia);
}

void optic_options::angle_spin_changed(qreal deg)
{
	if (deg < 0.0) deg += 360;
	else if (deg >= 360) deg -= 360;
	set_angle(deg);
}

void optic_options::up_btn_clicked() { move_pos(0, 10 / background->get_scale()); }
void optic_options::down_btn_clicked() { move_pos(0, -10 / background->get_scale()); }
void optic_options::left_btn_clicked() { move_pos(-10 / background->get_scale(), 0); }
void optic_options::right_btn_clicked() { move_pos(10 / background->get_scale(), 0); }

void optic_options::pos_changed()
{
	set_pos(ui->x_spin->value(), ui->y_spin->value());
}

void optic_options::outline_color_click()
{
	QColorDialog cd(current_outline_color, this);
	connect(&cd, SIGNAL(colorSelected(QColor)),
			this, SLOT(outline_color_changed(QColor)));
	cd.setModal(true);
	cd.exec();
}

void optic_options::material_color_click()
{
	QColorDialog cd(current_material_color, this);
	connect(&cd, SIGNAL(colorSelected(QColor)),
			this, SLOT(material_color_changed(QColor)));
	cd.setModal(true);
	cd.exec();
}

void optic_options::outline_color_changed(QColor c)
{
	c.setAlphaF(ui->outline_opacity_spin->value());
	set_outline_color(c);
}

void optic_options::outline_opacy_changed(double o)
{
	current_outline_color.setAlphaF(o);
	set_outline_color(current_outline_color);
}

void optic_options::material_color_changed(QColor c)
{
	c.setAlphaF(ui->material_opacity_spin->value());
	set_material_color(c);
}

void optic_options::material_opacy_changed(double o)
{
	current_material_color.setAlphaF(o);
	set_material_color(current_material_color);
}

void optic_options::delete_btn_click()
{
	background->delete_optic(opt);
	delete opt;
	background->recalc();
	background->update();
	accept();
}

void optic_options::reset() { restore(); }

void optic_options::cancel()
{
	restore();
	reject();
}

void optic_options::restore()
{
	set_pos(initial_pos.x(), initial_pos.y());
	set_angle(initial_angle);
	set_outline_color(initial_outline_color);
	set_material_color(initial_material_color);
	background->recalc();
	background->update();
}

void optic_options::set_material_color(QColor c)
{
	ui->material_opacity_spin->setValue(c.alphaF());
	current_material_color = c;
	QLabel *l = ui->material_color_preview;
	QPalette p = l->palette();
	c.setAlphaF(1);
	p.setColor(l->backgroundRole(), c);
	l->setPalette(p);
	opt->set_brush_color(current_material_color);
	background->update();
}

void optic_options::set_outline_color(QColor c)
{
	ui->outline_opacity_spin->setValue(c.alphaF());
	current_outline_color = c;
	QLabel *l = ui->outline_color_preview;
	QPalette p = l->palette();
	c.setAlphaF(1);
	p.setColor(l->backgroundRole(), c);
	l->setPalette(p);
	opt->set_pen_color(current_outline_color);
	background->update();
}

void optic_options::set_pos(qreal x, qreal y)
{
	ui->x_spin->blockSignals(true);
	ui->y_spin->blockSignals(true);

	current_pos.setX(x);
	current_pos.setY(y);
	ui->x_spin->setValue(x);
	ui->y_spin->setValue(y);

	ui->x_spin->blockSignals(false);
	ui->y_spin->blockSignals(false);

	opt->move_to(x, y);
	background->recalc();
	background->update();
}

void optic_options::move_pos(qreal inc_x, qreal inc_y)
{
	current_pos.setX(current_pos.x() + inc_x);
	current_pos.setY(current_pos.y() + inc_y);
	opt->move_by(inc_x, inc_y);
}

void optic_options::set_angle(qreal deg)
{
	ui->angle_dial->blockSignals(true);
	ui->angle_spin->blockSignals(true);

	ui->angle_dial->setValue( (((int) deg) + 90) % 360 );
	ui->angle_spin->setValue(deg);

	ui->angle_dial->blockSignals(false);
	ui->angle_spin->blockSignals(false);

    //opt->set_angle(qDegreesToRadians(deg));
    opt->set_angle(deg);

	background->recalc();
	background->update();
}

void optic_options::connect_angle()
{
	connect(ui->angle_dial, SIGNAL(valueChanged(int)),
			this, SLOT(angle_dial_changed(int)));
	connect(ui->angle_spin, SIGNAL(valueChanged(double)),
			this, SLOT(angle_spin_changed(qreal)));
	connect(ui->ccv_btn, SIGNAL(clicked(bool)),
			ui->angle_spin, SLOT(stepUp()));
	connect(ui->cv_btn, SIGNAL(clicked(bool)),
			ui->angle_spin, SLOT(stepDown()));
}

void optic_options::connect_movement()
{
	connect(ui->x_spin, SIGNAL(valueChanged(double)),
			this, SLOT(pos_changed()));
	connect(ui->y_spin, SIGNAL(valueChanged(double)),
			this, SLOT(pos_changed()));
	connect(ui->up_btn, SIGNAL(clicked(bool)),
			this, SLOT(up_btn_clicked()));
	connect(ui->down_btn, SIGNAL(clicked(bool)),
			this, SLOT(down_btn_clicked()));
	connect(ui->left_btn, SIGNAL(clicked(bool)),
			this, SLOT(left_btn_clicked()));
	connect(ui->right_btn, SIGNAL(clicked(bool)),
			this, SLOT(right_btn_clicked()));
}

void optic_options::connect_colors()
{
	connect(ui->outline_color_btn, SIGNAL(clicked(bool)),
			this, SLOT(outline_color_click()));
	connect(ui->outline_opacity_spin, SIGNAL(valueChanged(double)),
			this, SLOT(outline_opacy_changed(double)));
	connect(ui->material_color_btn, SIGNAL(clicked(bool)),
			this, SLOT(material_color_click()));
	connect(ui->material_opacity_spin, SIGNAL(valueChanged(double)),
			this, SLOT(material_opacy_changed(double)));
}

void optic_options::connect_buttons()
{
	connect(ui->reset_btn, SIGNAL(clicked(bool)),
			this, SLOT(reset()));
	connect(ui->buttonBox, SIGNAL(rejected()),
			this, SLOT(cancel()));
	connect(ui->delete_btn, SIGNAL(clicked(bool)),
			this, SLOT(delete_btn_click()));
}
