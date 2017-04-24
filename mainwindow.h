#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <gridscene.h>
#include <sourceitem.h>
#include <recieveritem.h>
#include <vertexitem.h>
#include <polygonitem.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QMainWindow *parent = 0);
	~MainWindow();
	void updateGraphicsViewSize();

private:
	void setSceneSize(int width, int height);
	void setViewOptions();
	void fillSelectionBox();
	void emptySelectionBox();
	void deleteSelectedItem();

private slots:
	void on_actionOpen_in_new_window_triggered();
	void on_actionAddSource_triggered();
	void on_actionAddReciever_triggered();
	void on_actionAddVertex_triggered();
	void on_actionAddPolygon_triggered();
	void on_setItemCoordinatesButton_clicked();
	void on_itemOptionsButton_clicked();
	void on_deleteItemButton_clicked();
	void on_itemSelected(MoveItem *selectedItem);
	void on_itemDragged(MoveItem *draggedItem);
	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
	void on_sceneMouseMoved(QPointF mousePosition);


private:
	Ui::MainWindow *ui;
	QGraphicsScene *scene;
	int sceneSizex;
	int sceneSizey;
	MoveItem *selectedItem = NULL;
	const int scrollbarThikness = 16;
};

#endif // MAINWINDOW_H
