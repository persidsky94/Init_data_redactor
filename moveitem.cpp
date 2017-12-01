#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) :
	QObject(parent), QGraphicsItem()
{
	connect(this, SIGNAL(itemSelected(MoveItem*)), parent, SLOT(on_itemSelected(MoveItem*)));
	connect(this, SIGNAL(itemDragged(MoveItem*)), parent, SLOT(on_itemDragged(MoveItem*)));
	this->setFlags(QGraphicsItem::ItemIgnoresTransformations);
}

MoveItem::~MoveItem()
{
}

QRectF MoveItem::boundingRect() const
{
	/* first 2 numbers - top left corner, last 2 - width and height */
	return QRectF (-12,-12,24,24);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(Qt::red);
	painter->setBrush(Qt::red);
	QLine firstCrossLine(-8,-8,8,8);
	QLine secondCrossLine(8,-8,-8,8);
	painter->drawLine(firstCrossLine);
	painter->drawLine(secondCrossLine);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	auto newCoordinates = this->pos() + (event->pos() - event->lastPos());
	auto validCoordinates = calculateValidCoordinates(newCoordinates);//this->pos() + (event->pos() - event->lastPos());//calculateValidCoordinates(event->pos());
	this->setPos(validCoordinates);
	emit positionIsSet();
	itemDragged(this);
}

QPointF MoveItem::calculateValidCoordinates(QPointF newCoordinates)
{
	/*
	QRectF sceneRect = (this->scene())->sceneRect();
	auto newx = mapToScene(mapFromParent(newCoordinates)).rx();
	auto newy = mapToScene(mapFromParent(newCoordinates)).ry();
	newx = std::max(newx, sceneRect.left());
	newx = std::min(newx, sceneRect.right());
	newy = std::max(newy, sceneRect.top());
	newy = std::min(newy, sceneRect.bottom());
	QPointF validCoordinates = mapToParent(mapFromScene(QPointF(newx, newy)));
	return validCoordinates;
	*/
	return newCoordinates;
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	this->setCursor(QCursor(Qt::ClosedHandCursor));
	emit itemSelected(this);
	Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	this->setCursor(QCursor(Qt::ArrowCursor));
	Q_UNUSED(event);
}
