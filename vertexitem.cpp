#include "vertexitem.h"

VertexItem::VertexItem(QObject *parent)
	: MoveItem(parent)
{
}

VertexItem::~VertexItem()
{
	emit vertexDeleted(this);
}

QRectF VertexItem::boundingRect() const
{
	/* first 2 numbers - top left corner, last 2 - width and height */
	return QRectF (-7,-7,14,14);
}

void VertexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = QPen(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::blue);
	painter->drawEllipse(-5,-5,10,10);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString VertexItem::getType()
{
	return QString("Polygon vertex");
}

void VertexItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	MoveItem::mouseMoveEvent(event);
	emit vertexMoved(this);
}

void VertexItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
			emit vertexAskToClone(this);
	else
		MoveItem::mousePressEvent(event);
}

void VertexItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	MoveItem::mouseReleaseEvent(event);
	emit vertexMoveFinished(this);
}
