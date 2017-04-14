#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include <moveitem.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();
	void updateGraphicsViewSizeAndAlignTopLeft();

private slots:
	void on_addSourceButton_clicked();
	void on_addItemOfType2Button_clicked();
	void on_setItemCoordinatesButton_clicked();
	void on_deleteItemButton_clicked();
	void on_itemSelected(MoveItem *selectedItem);
	void on_itemDragged(MoveItem *draggedItem);
	void on_zoomInButton_clicked();
	void on_zoomOutButton_clicked();
	void on_sceneMouseMoved(QGraphicsSceneMouseEvent *event);

	void on_debugButton_clicked();

private:
	Ui::Widget *ui;
	QGraphicsScene *scene;
	int sceneSizex;
	int sceneSizey;
	MoveItem *selectedItem = NULL;
	const int scrollbarThikness = 16;
//	const QReal


	void fillSelectionBox();
	void emptySelectionBox();
	void deleteSelectedItem();
};

#endif // WIDGET_H
