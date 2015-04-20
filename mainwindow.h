#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QVBoxLayout;
class field;
class QPushButton;
class QKeyEvent;

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);

	public slots:
		void keyPressEvent(QKeyEvent *ke);

	private:
		field *active_field;

};

#endif // MAINWINDOW_H
