#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <gridscene.h>
#include <editorsmanager.h>
#include <sceneserializer.h>
#include <sourceitem.h>
#include <recievergroup.h>
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

signals://to items list
	void itemAddedToScene(MoveItem *newItem, int listIndex);

private:
	void setSceneSize(int width, int height);
	void setViewOptions();
//	void fillSelectionBox();
//	void emptySelectionBox();
//	void deleteSelectedItem();

	void addNewSourceItem(sourceParams params);
	void addNewRecieverGroup(recieverGroupParams params);
	void addNewPolygonItem(polygonParams params);
	void addItemToScene(MoveItem *item);

	void bindSceneAndEditorsManager();
	void bindItemToScene(MoveItem *item);
	void bindActions();
	void setDefaultSourceParams();
	void setDefaultRecieverGroupParams();
	void setDefaultPolygonParams();

private slots:
	void on_actionOpen_in_new_window_triggered();
	void on_actionAddSource_triggered();
	void on_actionAddReciever_triggered();
	//void on_actionAddVertex_triggered();
	void on_actionAddPolygon_triggered();
	//void on_setItemCoordinatesButton_clicked();
	//void on_itemOptionsButton_clicked();
	//void on_deleteItemButton_clicked();
//	void on_itemSelected(MoveItem *selectedItem);
//	void on_itemDragged(MoveItem *draggedItem);
	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
//	void on_sceneMouseMoved(QPointF mousePosition);


	void on_actionSaveModel_triggered();
	void on_actionLoadModel_triggered();

private:
	Ui::MainWindow *ui;

	GridScene *_scene;
	EditorsManager *_editorsManager = NULL;
	ItemListManager *_listManager = NULL;
	SceneSerializer *_serializer;


	sourceParams _defaultSourceParams;
	recieverGroupParams _defaultRecieverGroupParams;
	polygonParams _defaultPolygonParams;

	int sceneSizex;
	int sceneSizey;
	MoveItem *selectedItem = NULL;
	const int scrollbarThikness = 16;

	void serializeScene();
	void deserializeScene();

	void bindSceneAndItemListManager();
	void bindSelfAndItemListManager();
};

#endif // MAINWINDOW_H
