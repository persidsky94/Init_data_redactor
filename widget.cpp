#include "widget.h"
#include "ui_widget.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
	return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	// Косметическая подготовка приложения
//	this->resize(750,640);          // Устанавливаем размеры окна приложения
	this->showMaximized();

	scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
	scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex/*NoIndex*/); // настраиваем индексацию элементов

	sceneSizex = 800;
	sceneSizey = 600;
	ui->xBox->setMaximum(sceneSizex);
	ui->yBox->setMaximum(sceneSizey);
	scene->setSceneRect(0,0,sceneSizex, sceneSizey);
	ui->graphicsView->resize(sceneSizex, sceneSizey);  // Устанавливаем размер graphicsView
	ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
	ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	ui->graphicsView->setMaximumSize(sceneSizex+scrollbarThikness, sceneSizey+scrollbarThikness);
	ui->graphicsView->resize(sceneSizex+scrollbarThikness, sceneSizey+scrollbarThikness);
	//setMouseTracking(true);
	//connect(scene, &QGraphicsScene::mouseMoveEvent, this, &Widget::on_sceneMouseMoved);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_addSourceButton_clicked()
{
	MoveItem *item = new MoveItem(QString("Source"),this);        // Создаём графический элемента
	item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
				 randomBetween(30,470));
	scene->addItem(item);   // Добавляем элемент на графическую сцену
}

void Widget::on_addItemOfType2Button_clicked()
{
	MoveItem *item = new MoveItem(QString("GorkMork"),this);        // Создаём графический элемента
	item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
				 randomBetween(30,470));
	scene->addItem(item);   // Добавляем элемент на графическую сцену
}

void Widget::on_itemSelected(MoveItem *item)
{
	selectedItem = item;
	fillSelectionBox();
}

void Widget::on_itemDragged(MoveItem *draggedItem)
{
	selectedItem = draggedItem;
	fillSelectionBox();
}

void Widget::fillSelectionBox()
{
	if (selectedItem != NULL)
	{
		QPointF itemCoordOnScene = selectedItem->mapToScene(QPointF(0,0));
		ui->xBox->setValue(itemCoordOnScene.rx());
		ui->yBox->setValue(itemCoordOnScene.ry());
		ui->type->setText(selectedItem->getType());
	}
}

void Widget::on_setItemCoordinatesButton_clicked()
{
	if (selectedItem != NULL)
	{
		QPointF newCoordinates = QPointF(ui->xBox->value(), ui->yBox->value());
		selectedItem->setPos(newCoordinates);
	}
}

void Widget::on_deleteItemButton_clicked()
{
	deleteSelectedItem();
	emptySelectionBox();
}

void Widget::deleteSelectedItem()
{
	if (selectedItem != NULL)
	{
		scene->removeItem(selectedItem);
		delete selectedItem;
		selectedItem = NULL;
	}
}

void Widget::emptySelectionBox()
{
	ui->xBox->setValue(0);
	ui->yBox->setValue(0);
	ui->type->setText("");
}

void Widget::on_zoomInButton_clicked()
{
	ui->graphicsView->scale(1.2, 1.2);
	updateGraphicsViewSizeAndAlignTopLeft();
}

void Widget::on_zoomOutButton_clicked()
{
	ui->graphicsView->scale(1/1.2, 1/1.2);
	updateGraphicsViewSizeAndAlignTopLeft();
}

void Widget::updateGraphicsViewSizeAndAlignTopLeft()
{
	QPointF zoomedSceneFarCorner = ui->graphicsView->mapFromScene(scene->sceneRect().bottomRight());
	QPointF zoomedSceneZeroCorner = ui->graphicsView->mapFromScene(scene->sceneRect().topLeft());
	int sceneWidth = zoomedSceneFarCorner.rx() - zoomedSceneZeroCorner.rx();
	int sceneHeight = zoomedSceneFarCorner.ry() - zoomedSceneZeroCorner.ry();
	ui->graphicsView->setMaximumSize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);
	ui->graphicsView->resize(sceneWidth+scrollbarThikness, sceneHeight+scrollbarThikness);

	ui->horizontalLayout->setAlignment(ui->verticalLayout, Qt::AlignTop);
	ui->verticalLayout->setAlignment(ui->verticalLayout_12, Qt::AlignTop);
	ui->horizontalLayout->setAlignment(ui->verticalLayout, Qt::AlignLeft);
	ui->verticalLayout->setAlignment(ui->verticalLayout_12, Qt::AlignLeft);

	this->updateGeometry();
}

void Widget::on_sceneMouseMoved(QGraphicsSceneMouseEvent *event)
{
	QPointF mousePosition = event->pos();
	ui->mousex->setValue(mousePosition.rx());
	ui->mousey->setValue(mousePosition.ry());
}


void Widget::on_debugButton_clicked()
{
	QPointF zoomedSceneFarCorner = ui->graphicsView->mapFromScene(scene->sceneRect().bottomRight());
	int sceneWidth = zoomedSceneFarCorner.rx();
	int sceneHeight = zoomedSceneFarCorner.ry();
	ui->debugLine->setText(QString::number(sceneWidth + scrollbarThikness) + QString(" ") + QString::number(sceneHeight + scrollbarThikness) + QString(" ") + \
						   QString::number(ui->graphicsView->width()) + QString(" ") + QString::number(ui->graphicsView->height()) + \
						   QString(" ") + QString::number(scene->sceneRect().width()) + QString(" ") + QString::number(scene->sceneRect().height()));
}
