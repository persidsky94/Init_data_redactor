#include "sourceitem.h"

SourceItem::SourceItem(sourceParams params, QObject *parent)
	: MoveItem(parent), _params(params)
{
	connect(this, &SourceItem::positionIsSet, this, &SourceItem::on_positionIsSet);
	setParams(params);
}

SourceItem::~SourceItem()
{
}

QRectF SourceItem::boundingRect() const
{
	/* first 2 numbers - top left corner, last 2 - width and height */
	return QRectF (-_sourceSize/2,-_sourceSize/2,_sourceSize,_sourceSize);
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
	return QString("source");
}

sourceParams SourceItem::getParams()
{
	return _params;
}

void SourceItem::on_positionIsSet()
{
	auto params = _params;
	params.x = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
}

void SourceItem::setParams(sourceParams params)
{
	auto prevBoundingRect = boundingRect();
	bool name_has_changed = 0;
	if (params.name != _params.name)
		name_has_changed = 1;

	_params = params;
//	_params.x = params.x;
//	_params.y = params.y;
//	_params.name = params.name;
//	_params.signalType = params.signalType;

	auto newCoordinates = QPointF(_params.x, _params.y);
	setPos(newCoordinates);
	auto curBoundingRect = boundingRect();
	if (name_has_changed)
		emit nameChanged(this);
	emit paramsChanged(_params);
	if (this->scene())
	{
		this->scene()->update(mapRectToScene(prevBoundingRect));
		this->scene()->update(mapRectToScene(curBoundingRect));
	}
}
