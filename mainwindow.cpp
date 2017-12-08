#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDialogButtonBox>

static int randomBetween(int low, int high)
{
	return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	bindActions();
	setDefaultSourceParams();
	setDefaultRecieverGroupParams();
	setDefaultPolygonParams();
	//this->ui->centralWidget->layout()->setSizeConstraint();
	_editorsManager = new EditorsManager(this);
	bool needDuplicateButton = false;
	_listManager = new ItemListManager(this, needDuplicateButton);
	_scene = new GridScene(this);
	bindSceneAndEditorsManager();
	bindSceneAndItemListManager();
	bindSelfAndItemListManager();
	this->ui->sceneWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->centralWidget->layout()->addWidget(_listManager->getWidget());
	this->ui->centralWidget->layout()->addWidget(_editorsManager->getWidget());
	_scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex/*NoIndex*/);
	setSceneSize(800,600);

	ui->graphicsView->setScene(_scene);
	setViewOptions();
	updateGraphicsViewSize();

	ui->graphicsView->setMouseTracking(true);

	this->showMaximized();

//	connect(_scene, SIGNAL(mouseAt(QPointF)), this, SLOT(on_sceneMouseMoved(QPointF)));
}

void MainWindow::setSceneSize(int width, int height)
{
	sceneSizex = width;
	sceneSizey = height;
	/*
	ui->xBox->setMaximum(sceneSizex);
	ui->yBox->setMaximum(sceneSizey);
	ui->mousex->setMaximum(sceneSizex);
	ui->mousey->setMaximum(sceneSizey);
	*/
	_scene->setSceneRect(0,0,sceneSizex, sceneSizey);
}

void MainWindow::setViewOptions()
{
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
	ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::/*BoundingRectViewportUpdate*/FullViewportUpdate);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionAddSource_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new SourceInfo(dialog);
	initEditor->initWithParams(_defaultSourceParams);
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		addNewSourceItem(params);
	}
	delete dialog;
}

void MainWindow::on_actionAddReciever_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new RecieverGroupInfo(dialog);
	initEditor->initWithParams(_defaultRecieverGroupParams);
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		addNewRecieverGroup(params);
	}
	delete dialog;
}

void MainWindow::on_actionAddPolygon_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new PolygonInfo(dialog);
	initEditor->initWithParams(_defaultPolygonParams);
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		addNewPolygonItem(params);
	}
	delete dialog;
}

/*
void MainWindow::on_actionAddVertex_triggered()
{
	MoveItem *item = new VertexItem(this);
	item->setPos(randomBetween(30, 470),
				 randomBetween(30,470));
	_scene->addItem(item);
}

void MainWindow::on_itemSelected(MoveItem *item)
{
	selectedItem = item;
	fillSelectionBox();
}

void MainWindow::on_itemDragged(MoveItem *draggedItem)
{
	selectedItem = draggedItem;
	fillSelectionBox();
}

void MainWindow::fillSelectionBox()
{
	if (selectedItem != NULL)
	{
		QPointF itemCoordOnScene = selectedItem->mapToScene(QPointF(0,0));
		ui->xBox->setValue(itemCoordOnScene.rx());
		ui->yBox->setValue(itemCoordOnScene.ry());
		ui->type->setText(selectedItem->getType());
	}
}

void MainWindow::on_setItemCoordinatesButton_clicked()
{
	if (selectedItem != NULL)
	{
		QPointF newCoordinates = QPointF(ui->xBox->value(), ui->yBox->value());
		selectedItem->setPos(newCoordinates);
	}
}

void MainWindow::on_itemOptionsButton_clicked()
{
	if (selectedItem != NULL)
	{
		if (selectedItem->getType() == QString("Source"))
		{
			auto source = ((SourceItem *)selectedItem);
			SourceOptions *dialog = new SourceOptions(this, _scene->sceneRect(), source->getParams());
			if (dialog->exec())
			{
				SourceOptions::source_params params = dialog->getParams();
				source->setParams(params);
			}
			delete dialog;
		}
	}
}

void MainWindow::on_deleteItemButton_clicked()
{
	deleteSelectedItem();
	emptySelectionBox();
}

void MainWindow::deleteSelectedItem()
{
	if (selectedItem != NULL)
	{
		_scene->removeItem(selectedItem);
		delete selectedItem;
		selectedItem = NULL;
	}
}

void MainWindow::emptySelectionBox()
{
	ui->xBox->setValue(0);
	ui->yBox->setValue(0);
	ui->type->setText("");
}
*/
void MainWindow::on_actionZoomIn_triggered()
{
	ui->graphicsView->scale(1.2, 1.2);
	updateGraphicsViewSize();
}

void MainWindow::on_actionZoomOut_triggered()
{
	ui->graphicsView->scale(1/1.2, 1/1.2);
	updateGraphicsViewSize();
}

void MainWindow::updateGraphicsViewSize()
{
	QPointF zoomedSceneFarCorner = ui->graphicsView->mapFromScene(_scene->sceneRect().bottomRight());
	QPointF zoomedSceneZeroCorner = ui->graphicsView->mapFromScene(_scene->sceneRect().topLeft());
	int sceneWidth = zoomedSceneFarCorner.rx() - zoomedSceneZeroCorner.rx();
	int sceneHeight = zoomedSceneFarCorner.ry() - zoomedSceneZeroCorner.ry();
	ui->graphicsView->setMaximumSize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);
	ui->graphicsView->resize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);

	this->updateGeometry();
}

/*
void MainWindow::on_sceneMouseMoved(QPointF mousePosition)
{
	ui->mousex->setValue(mousePosition.rx());
	ui->mousey->setValue(mousePosition.ry());
}
*/

void MainWindow::on_actionOpen_in_new_window_triggered()
{
	auto newCalc = new MainWindow();
}

void MainWindow::addNewSourceItem(sourceParams params)
{
	auto src = new SourceItem(params, this);
	addItemToScene(src);
	src->itemSelected(src);
}

void MainWindow::addNewRecieverGroup(recieverGroupParams params)
{
	auto src = new RecieverGroup(params, this);
	addItemToScene(src);
	src->itemSelected(src);
}

void MainWindow::addNewPolygonItem(polygonParams params)
{
	auto poly = new PolygonItem(params, this);
	addItemToScene(poly);
	poly->itemSelected(poly);
}

void MainWindow::addItemToScene(MoveItem *item)
{
	_scene->addItem(item);
	bindItemToScene(item);
	emit itemAddedToScene(item, 0);
}

void MainWindow::bindSelfAndItemListManager()
{
	QObject::connect(this, &MainWindow::itemAddedToScene, _listManager, &ItemListManager::on_itemAddedToContainer);
}

void MainWindow::bindSceneAndItemListManager()
{
	QObject::connect(_scene, &GridScene::sceneItemNameChanged, _listManager, &ItemListManager::on_containerItemNameChanged);
	QObject::connect(_scene, &GridScene::sceneItemSelected, _listManager, &ItemListManager::on_itemSelectedInContainer);
	QObject::connect(_scene, &GridScene::sceneItemDeleted, _listManager, &ItemListManager::on_itemDeletedFromContainer);
	QObject::connect(_listManager, &ItemListManager::selectContainerItem, _scene, &GridScene::on_selectSceneItem);
	QObject::connect(_listManager, &ItemListManager::deleteContainerItemByPtr, _scene, &GridScene::on_deleteSceneItem);
}

void MainWindow::bindSceneAndEditorsManager()
{
	QObject::connect(_scene, &GridScene::sceneItemSelected, _editorsManager, &EditorsManager::changeRedactedItem);
}

void MainWindow::bindItemToScene(MoveItem *item)
{
	QObject::connect(item, &MoveItem::itemSelected, _scene, &GridScene::on_sceneItemSelected);
	QObject::connect(item, &MoveItem::nameChanged, _scene, &GridScene::on_itemNameChanged);
}

void MainWindow::bindActions()
{
	//connect(this->ui->actionAddSource, &QAction::triggered, this, &MainWindow::on_actionAddSource_triggered);
}

void MainWindow::setDefaultSourceParams()
{
	_defaultSourceParams.name = QString("Source");
	_defaultSourceParams.x = 0;
	_defaultSourceParams.y = 0;
	_defaultSourceParams.signalType = sourceParams::Sin;
}

void MainWindow::setDefaultRecieverGroupParams()
{
	_defaultRecieverGroupParams.name = QString("Recievers horizontal group");
	_defaultRecieverGroupParams.firstx = 0;
	_defaultRecieverGroupParams.deltax = 10;
	_defaultRecieverGroupParams.y = 100;
	_defaultRecieverGroupParams.recieversNumber = 20;
}

void MainWindow::setDefaultPolygonParams()
{
	_defaultPolygonParams.name = QString("Polygon");
	_defaultPolygonParams.density = 1000;
	_defaultPolygonParams.x = 30;
	_defaultPolygonParams.y = 30;
}
