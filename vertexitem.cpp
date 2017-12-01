#include "vertexitem.h"

VertexItem::VertexItem(vertexParams params, QObject *parent)
	: MoveItem(parent), _params(params)
{
	connect(this, &VertexItem::positionIsSet, this, &VertexItem::on_positionIsSet);
	setParams(params);
}

VertexItem::~VertexItem()
{
	emit vertexDeleted(this);
}

void VertexItem::setParams(vertexParams params)
{
	/*
	auto prevBoundingRect = boundingRect();
	bool name_has_changed = 0;
	if (params.name != _params.name)
		name_has_changed = 1;
	_params = params;
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
	*/
}

void VertexItem::on_positionIsSet()
{
	auto params = _params;
	params.x = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
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

vertexParams VertexItem::getParams()
{
	return _params;
}
