#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QVBoxLayout;
class field;
class QPushButton;

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);

	private:
		field *mainfield;
		QPushButton *left_btn;
		QPushButton *right_btn;
		QPushButton *up_btn;
		QPushButton *down_btn;
};

#endif // MAINWINDOW_H
