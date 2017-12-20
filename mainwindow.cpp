#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QProcess>

static int randomBetween(int low, int high)
{
	return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	bool needDuplicateButton = false;
	_sceneManager = new SceneManager(this);
	_listManager = new ItemListManager(this, needDuplicateButton);
	_editorsManager = new EditorsManager(this);

	bindSceneManagerAndEditorsManager();
	bindSceneManagerAndItemListManager();
	bindSceneContainerAndItemListManager();

	this->ui->sceneWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->centralWidget->layout()->addWidget(_listManager->getWidget());
	this->ui->centralWidget->layout()->addWidget(_editorsManager->getWidget());

	ui->graphicsView->setScene(_sceneManager->getScene());
	setViewOptions();
	updateGraphicsViewSize();

	ui->graphicsView->setMouseTracking(true);

	this->showMaximized();
//	connect(_scene, SIGNAL(mouseAt(QPointF)), this, SLOT(on_sceneMouseMoved(QPointF)));
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
	initEditor->initWithParams(_sceneManager->getDefaultSourceParams());
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		_sceneManager->addNewSourceItem(params);
	}
	delete dialog;
}

void MainWindow::on_actionAddReciever_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new RecieverGroupInfo(dialog);
	initEditor->initWithParams(_sceneManager->getDefaultRecieverGroupParams());
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		_sceneManager->addNewRecieverItem(params);
	}
	delete dialog;
}

void MainWindow::on_actionAddPolygon_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new PolygonInfo(dialog);
	initEditor->initWithParams(_sceneManager->getDefaultPolygonParams());
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		_sceneManager->addNewPolygonItem(params);
	}
	delete dialog;
}

/*

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
	QPointF zoomedSceneFarCorner = ui->graphicsView->mapFromScene(_sceneManager->getScene()->sceneRect().bottomRight());
	QPointF zoomedSceneZeroCorner = ui->graphicsView->mapFromScene(_sceneManager->getScene()->sceneRect().topLeft());
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

void MainWindow::bindSceneManagerAndItemListManager()
{
	QObject::connect(_sceneManager, &SceneManager::itemAddedToScene, _listManager, &ItemListManager::on_itemAddedToContainer);
	QObject::connect(_sceneManager, &SceneManager::sceneItemNameChanged, _listManager, &ItemListManager::on_containerItemNameChanged);
	QObject::connect(_sceneManager, &SceneManager::sceneItemSelected, _listManager, &ItemListManager::on_itemSelectedInContainer);
	QObject::connect(_sceneManager, &SceneManager::sceneItemDeleted, _listManager, &ItemListManager::on_itemDeletedFromContainer);
	QObject::connect(_listManager, &ItemListManager::selectContainerItem, _sceneManager, &SceneManager::selectSceneItem);
	QObject::connect(_listManager, &ItemListManager::deleteContainerItemByPtr, _sceneManager, &SceneManager::removeItemFromScene);
}

void MainWindow::bindSceneManagerAndEditorsManager()
{
	QObject::connect(_sceneManager, &SceneManager::sceneItemSelected, _editorsManager, &EditorsManager::changeRedactedItem);
	QObject::connect(_sceneManager, &SceneManager::sceneCleared, _editorsManager, &EditorsManager::on_sceneCleared);
}

void MainWindow::bindSceneContainerAndItemListManager()
{
	QObject::connect(_sceneManager->getItemContainer(), &SceneItemContainer::containerCleared, _listManager, &ItemListManager::on_containerCleared);
}

void MainWindow::on_actionSaveModel_triggered()
{
	_sceneManager->serializeSceneToFile();
}

void MainWindow::on_actionLoadModel_triggered()
{
	_sceneManager->deserializeSceneFromFile();
}

void MainWindow::on_actionConfigureScene_triggered()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto initEditor = new SceneInfo(dialog);
	initEditor->initWithParams(_sceneManager->getScene()->getParams());
	initEditor->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(initEditor);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = initEditor->constructParams();
		_sceneManager->setSceneParams(params);
	}
	delete dialog;
}

void MainWindow::on_actionConvertToInitData_triggered()
{
    _sceneManager->convertToInitData();
}

void MainWindow::on_actionBeginCalculation_triggered()
{
    auto p = new QProcess();
    p->setWorkingDirectory(_sceneManager->getPathToCalcDir());
    QString file = _sceneManager->getPathToCalcDir() + QString("/acoustic_2d");
    QStringList params;
    params << _sceneManager->getPathToCalcDir() + QString("/config.hrdata");

    auto dialog = new QDialog(this);
    auto layout = new QVBoxLayout(dialog);
    auto label = new QLabel("Calculating...");
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, dialog);
    layout->addWidget(label);
    layout->addWidget(buttonBox);
 //   QObject::connect(p, &QProcess::finished, this, &MainWindow::on_calcProcessFinished);
    QObject::connect(this, &MainWindow::calculationFinished, dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, p, &QProcess::terminate);

    p->start(file, params);

    dialog->exec();
    delete dialog;

}

void MainWindow::on_calcProcessFinished(int status)
{
    emit calculationFinished();
}
