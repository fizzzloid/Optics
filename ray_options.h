#ifndef RAY_OPTIONS_H
#define RAY_OPTIONS_H

#include <QDialog>

namespace Ui {
class ray_options;
}

class ray_options : public QDialog
{
		Q_OBJECT

	public:
		explicit ray_options(QWidget *parent = 0);
		~ray_options();

	private:
		Ui::ray_options *ui;
};

#endif // RAY_OPTIONS_H
