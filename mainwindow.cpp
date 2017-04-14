#include "mainwindow.h"
#include "ui_mainwindow.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
	return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->showMaximized();

	scene = new GridScene(this);   // Инициализируем графическую сцену
	scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex/*NoIndex*/); // настраиваем индексацию элементов
	setSceneSize(800,600);

	ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
	setViewOptions();
	updateGraphicsViewSize();

	ui->graphicsView->setMouseTracking(true);

	connect(scene, SIGNAL(mouseAt(QPointF)), this, SLOT(on_sceneMouseMoved(QPointF)));
}

void MainWindow::setSceneSize(int width, int height)
{
	sceneSizex = width;
	sceneSizey = height;
	ui->xBox->setMaximum(sceneSizex);
	ui->yBox->setMaximum(sceneSizey);
	ui->mousex->setMaximum(sceneSizex);
	ui->mousey->setMaximum(sceneSizey);
	scene->setSceneRect(0,0,sceneSizex, sceneSizey);
}

void MainWindow::setViewOptions()
{
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
	ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::/*BoundingRectViewportUpdate*/FullViewportUpdate);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionAddSource_triggered()
{
	MoveItem *item = new SourceItem(this);        // Создаём графический элемента
	item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
				 randomBetween(30,470));
	scene->addItem(item);   // Добавляем элемент на графическую сцену
}

void MainWindow::on_addItemOfType2Button_clicked()
{
	MoveItem *item = new RecieverItem(this);        // Создаём графический элемента
	item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
				 randomBetween(30,470));
	scene->addItem(item);   // Добавляем элемент на графическую сцену
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

void MainWindow::on_deleteItemButton_clicked()
{
	deleteSelectedItem();
	emptySelectionBox();
}

void MainWindow::deleteSelectedItem()
{
	if (selectedItem != NULL)
	{
		scene->removeItem(selectedItem);
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

void MainWindow::on_zoomInButton_clicked()
{
	ui->graphicsView->scale(1.2, 1.2);
	updateGraphicsViewSize();
}

void MainWindow::on_zoomOutButton_clicked()
{
	ui->graphicsView->scale(1/1.2, 1/1.2);
	updateGraphicsViewSize();
}

void MainWindow::updateGraphicsViewSize()
{
	QPointF zoomedSceneFarCorner = ui->graphicsView->mapFromScene(scene->sceneRect().bottomRight());
	QPointF zoomedSceneZeroCorner = ui->graphicsView->mapFromScene(scene->sceneRect().topLeft());
	int sceneWidth = zoomedSceneFarCorner.rx() - zoomedSceneZeroCorner.rx();
	int sceneHeight = zoomedSceneFarCorner.ry() - zoomedSceneZeroCorner.ry();
	ui->graphicsView->setMaximumSize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);
	ui->graphicsView->resize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);

	this->updateGeometry();
}

void MainWindow::on_sceneMouseMoved(QPointF mousePosition)
{
	ui->mousex->setValue(mousePosition.rx());
	ui->mousey->setValue(mousePosition.ry());
}


void MainWindow::on_debugButton_clicked()
{
	scene->invalidate(scene->sceneRect());
	scene->update();
	ui->graphicsView->repaint();
	ui->graphicsView->update();
	ui->graphicsView->viewport()->update();
}
