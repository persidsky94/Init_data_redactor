#include "recievergroup.h"

RecieverGroup::RecieverGroup(recieverGroupParams params, QObject *parent)
	:MoveItem(parent), _params(params)
{
	connect(this, &RecieverGroup::positionIsSet, this, &RecieverGroup::on_positionIsSet);
	setParams(params);
}

RecieverGroup::~RecieverGroup(){}

QRectF RecieverGroup::boundingRect() const
{
	auto params = getParams();
	return QRectF(0, 0, params.deltax*params.recieversNumber, _singleRecieverThickness);
}

void RecieverGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = QPen(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);
	painter->setBrush(Qt::yellow);
	std::vector<float> recieversXCoordinates;
	auto params = getParams();
	float currentXCoordinate = params.firstx;
	for (int i=0; i<params.recieversNumber; ++i)
	{
		recieversXCoordinates.push_back(currentXCoordinate);
		currentXCoordinate += params.deltax;
	}
	for (auto coord : recieversXCoordinates)
		drawSingleReciever(painter, coord, params.y);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void RecieverGroup::drawSingleReciever(QPainter *painter, float x, float y)
{
	painter->drawRect(x-_singleRecieverThickness, y-_singleRecieverThickness, _singleRecieverThickness, _singleRecieverThickness);
}

QString RecieverGroup::getType()
{
	return QString("reciever group");
}

recieverGroupParams RecieverGroup::getParams()
{
	return _params;
}

void RecieverGroup::on_positionIsSet()
{
	auto params = _params;
	params.firstx = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
}

void RecieverGroup::setParams(recieverGroupParams params)
{
	auto prevBoundingRect = boundingRect();
	bool name_has_changed = 0;
	if (params.name != _params.name)
		name_has_changed = 1;
	_params = params;
	auto newCoordinates = QPointF(_params.firstx, _params.y);
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

QPointF RecieverGroup::calculateValidCoordinates(QPointF newCoordinates)
{
	QRectF sceneBR = this->scene()->sceneRect();
	auto offset = newCoordinates - this->pos();
	QRectF BR = this->getBoundingRect();
	auto topleft = BR.topLeft();
	BR.moveTopLeft(topleft + offset);
	QPointF realOffset = offset;
	auto sceneTopLeft = sceneBR.topLeft();
	auto sceneBottomRight = sceneBR.bottomRight();
	topleft = mapToParent(BR.topLeft());
	auto bottomright = mapToParent(BR.bottomRight());
	auto delta = topleft - sceneTopLeft;
	if (delta.ry() < 0) realOffset -= QPointF(0, delta.ry());
	if (delta.rx() < 0) realOffset -= QPointF(delta.rx(), 0);
	delta = bottomright - sceneBottomRight;
	if (delta.ry() > 0) realOffset -= QPointF(0, delta.ry());
	if (delta.rx() > 0) realOffset -= QPointF(delta.rx(), 0);
	QPointF validCoordinates = (this->pos() + realOffset);
	return validCoordinates;
}
