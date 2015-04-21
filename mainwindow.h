#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QVBoxLayout;
class field;
class QPushButton;
class QKeyEvent;
class QLabel;

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);

	public slots:
		void keyPressEvent(QKeyEvent *ke);
		void status_changed();

	private:
		void setup_statusbar();

		field *active_field;
		QLabel *navigation_label;
};

#endif // MAINWINDOW_H
