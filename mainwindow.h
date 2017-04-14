#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <gridscene.h>
#include <sourceitem.h>
#include <recieveritem.h>

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

private slots:
	void on_actionAddSource_triggered();
	void on_addItemOfType2Button_clicked();
	void on_setItemCoordinatesButton_clicked();
	void on_deleteItemButton_clicked();
	void on_itemSelected(MoveItem *selectedItem);
	void on_itemDragged(MoveItem *draggedItem);
	void on_zoomInButton_clicked();
	void on_zoomOutButton_clicked();
	void on_sceneMouseMoved(QPointF mousePosition);

	void on_debugButton_clicked();

private:
	Ui::MainWindow *ui;
	QGraphicsScene *scene;
	int sceneSizex;
	int sceneSizey;
	MoveItem *selectedItem = NULL;
	const int scrollbarThikness = 16;


	void fillSelectionBox();
	void emptySelectionBox();
	void deleteSelectedItem();
};

#endif // MAINWINDOW_H
