#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <gridscene.h>
#include <sceneinfo.h>
#include <scenemanager.h>
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

signals:
    void calculationFinished();

private:
	Ui::MainWindow *ui;
	const int scrollbarThikness = 16;

	SceneManager *_sceneManager;
	EditorsManager *_editorsManager = NULL;
	ItemListManager *_listManager = NULL;


	void setViewOptions();
	void updateGraphicsViewSize();

	void bindSceneManagerAndEditorsManager();
	void bindSceneManagerAndItemListManager();
	void bindSceneContainerAndItemListManager();

private slots:
	void on_actionOpen_in_new_window_triggered();
	void on_actionSaveModel_triggered();
	void on_actionLoadModel_triggered();
	void on_actionConfigureScene_triggered();
    void on_actionConvertToInitData_triggered();
    void on_actionBeginCalculation_triggered();

	void on_actionAddSource_triggered();
	void on_actionAddReciever_triggered();
	void on_actionAddPolygon_triggered();

	void on_actionZoomIn_triggered();
	void on_actionZoomOut_triggered();
//	void on_sceneMouseMoved(QPointF mousePosition);
//	void on_itemSelected(MoveItem *selectedItem);
//	void on_itemDragged(MoveItem *draggedItem);
    void on_calcProcessFinished(int status);



};

#endif // MAINWINDOW_H
