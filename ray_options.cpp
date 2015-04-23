#include "ray_options.h"
#include "ui_ray_options.h"

ray_options::ray_options(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ray_options)
{
	ui->setupUi(this);
}

ray_options::~ray_options()
{
	delete ui;
}
