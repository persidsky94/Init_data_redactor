#include "sourceitem.h"

SourceItem::SourceItem(QObject *parent)
	: MoveItem(parent)
{
}

SourceItem::~SourceItem()
{
}

QRectF SourceItem::boundingRect() const
{
	/* first 2 numbers - top left corner, last 2 - width and height */
	return QRectF (-12,-12,24,24);
}

void SourceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = QPen(Qt::red);
	pen.setWidth(2);
	painter->setPen(pen);
	painter->setBrush(Qt::red);
	QLine firstCrossLine(-8,-8,8,8);
	QLine secondCrossLine(8,-8,-8,8);
	painter->drawLine(firstCrossLine);
	painter->drawLine(secondCrossLine);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString SourceItem::getType()
{
	return QString("Source");
}
