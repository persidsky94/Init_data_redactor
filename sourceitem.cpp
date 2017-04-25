#include "sourceitem.h"

SourceItem::SourceItem(SourceOptions::source_params params, QObject *parent)
	: MoveItem(parent)
{
	setParams(params);
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

SourceOptions::source_params SourceItem::getParams()
{
	return SourceOptions::source_params(name, type, signal, this->pos().rx(), this->pos().ry());
}

void SourceItem::setParams(SourceOptions::source_params params)
{
	name = params.name;
	type = params.sourceType;
	signal = params.signalType;
	this->setPos(params.x, params.y);
}

void SourceItem::on_optionsButton_clicked()
{

}
