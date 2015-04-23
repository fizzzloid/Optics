#ifndef OBJ_SELECTION_MENU_H
#define OBJ_SELECTION_MENU_H

#include <QMenu>
#include <QSet>
class obj_selection_menu : public QMenu
{
		Q_OBJECT

	public:
		obj_selection_menu(QSet<qint32> hl_rays, QSet<qint32> hl_optics,
						   QWidget *parent = 0);
		~obj_selection_menu();

	signals:
		void mouse_on_ray(qint32 num);
		void mouse_on_optic(qint32 num);
		void ray_selected(qint32 num);
		void optic_selected(qint32 num);

	private slots:
		void on_ray();
		void on_optic();
		void click_ray();
		void click_optic();
};

#endif // OBJ_SELECTION_MENU_H
