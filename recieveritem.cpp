#include "recieveritem.h"

RecieverItem::RecieverItem(QObject *parent)
	: MoveItem(parent)
{
}

RecieverItem::~RecieverItem()
{
}

QRectF RecieverItem::boundingRect() const
{
	/* first 2 numbers - top left corner, last 2 - width and height */
	return QRectF (-8,-8,16,16);
}

void RecieverItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(Qt::black);
	painter->setBrush(Qt::yellow);
	QRectF square = QRectF(-6,-6,12,12);
	painter->drawRect(square);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString RecieverItem::getType()
{
	return QString("Reciever");
}
