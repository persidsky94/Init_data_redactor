#include "gridscene.h"

GridScene::GridScene(sceneParams params, QObject *parent)
	: QGraphicsScene(parent)
{
	setBackgroundGrid();
	setParams(params);
	this->setItemIndexMethod(QGraphicsScene::BspTreeIndex/*NoIndex*/);
}

void GridScene::setBackgroundGrid()
{
	int gridSizeX = 45;
	int gridSizeY = 35;
	QImage singleGrid( gridSizeX, gridSizeY, QImage::Format_RGB32 );
	singleGrid.fill( Qt::white );
	{
		QPainter painter( &singleGrid );

		// Lighter background
		QPen p = QPen( QColor( 240, 240, 240 ) );
		p.setWidth(2);
		painter.setPen(p);

		qreal midx = gridSizeX / 2;
		qreal midy = gridSizeY / 2;
		painter.drawLine( 0, midy, gridSizeX, midy );
		painter.drawLine( midx, 0, midx, gridSizeY );

		// Darker foregound
		//p.setColor(QColor( 180, 180, 180 ));
		painter.setPen(p);
		painter.drawRect( 0, 0, gridSizeX, gridSizeY );

		painter.end();
	}
	QBrush brushBackground( singleGrid );
	setBackgroundBrush( brushBackground );
}

void GridScene::drawBorders()
{
    auto width = _params.nodes_x * _params.space_step_x;
    auto height = _params.nodes_y * _params.space_step_y;
	auto borderPen = QPen(QColor(0,0,0));
	auto borderPainter = new QPainter;
	borderPainter->setPen(borderPen);
	borderPainter->drawRect(0,0,width,height);
}

void GridScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsScene::drawBackground(painter, rect);
	drawBorders();
/*	int gridSize = std::min(this->height()/15, this->width()/15);

	auto r = this->sceneRect();
	qreal left = r.left();
	qreal top = r.top();

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < r.right(); x += gridSize)
		lines.append(QLineF(x, r.top(), x, r.bottom()));
	for (qreal y = top; y < r.bottom(); y += gridSize)
		lines.append(QLineF(r.left(), y, r.right(), y));

	painter->drawLines(lines.data(), lines.size());*/
}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
	emit mouseAt(event->scenePos());
}

void GridScene::on_sceneItemSelected(MoveItem *item)
{
	emit sceneItemSelected(item);
}

void GridScene::on_itemNameChanged(MoveItem *item)
{
	emit sceneItemNameChanged(item);
}

void GridScene::on_selectSceneItem(MoveItem *item)
{
	emit sceneItemSelected(item);
}

void GridScene::on_deleteSceneItem(MoveItem *item)
{
	emit sceneItemDeleted(item);
	this->removeItem(item);
}

void GridScene::addItem(QGraphicsItem *item)
{
//	_itemContainer.addItemToContainer(dynamic_cast<MoveItem *>(item));
	QGraphicsScene::addItem(item);
}

void GridScene::removeItem(QGraphicsItem *item)
{
//	_itemContainer.deleteItemFromContainer(dynamic_cast<MoveItem *>(item));
	emit sceneItemDeleted(dynamic_cast<MoveItem *>(item));
	QGraphicsScene::removeItem(item);
}

void GridScene::setParams(sceneParams params)
{
	_params = params;
    this->setSceneRect(0, 0, _params.nodes_x * _params.space_step_x, _params.nodes_y * _params.space_step_y);
}
