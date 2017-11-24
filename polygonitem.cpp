#include "polygonitem.h"

PolygonItem::PolygonItem(polygonParams params, QObject *parent)
	: MoveItem(parent), _params(params)
{
	this->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
	connect(this, &PolygonItem::positionIsSet, this, &PolygonItem::on_positionIsSet);
//	QPointF pos = QPointF(200,200);
//	this->setPos(pos);
	setParams(params);
	int vertexIndex = 0;
	qreal vertexLocalx = 0;
	qreal vertexLocaly = 0;
	createChildVertex(vertexIndex, vertexLocalx, vertexLocaly);
}

VertexItem *PolygonItem::createChildVertex(int index, qreal localx, qreal localy)
{
	if (index >= pVertices.size())
		index = pVertices.size();
	if (index < 0)
		index = 0;
	VertexItem *vertex = new VertexItem(this);
	vertex->setParentItem(this);
	vertex->setPos(localx, localy);
	pVertices.insert(index, vertex);
	bindVertexSignals(vertex);
	updateVerticesPolygon();
	if ((localx < 0) || (localy < 0))
		updatePolygonPosToTopLeftOfVerticesBoundingRect();
	emit childVertexCreated(this, vertex);
}

void PolygonItem::updatePolygonPosToTopLeftOfVerticesBoundingRect()
{
	auto BR = boundingRect();
	auto topLeftBR = BR.topLeft();
	auto params = _params;
	params.x = this->pos().toPoint().x() + topLeftBR.rx();
	params.y = this->pos().toPoint().y() + topLeftBR.ry();
	moveAllVertecesBy(-topLeftBR.rx(), -topLeftBR.ry());
	updateVerticesPolygon();
	setParams(params);
}

//moves all vertices by vector (localx, localy)
void PolygonItem::moveAllVertecesBy(qreal localx, qreal localy)
{
	for (int i=0; i<pVertices.size(); ++i)
	{
		auto prevx = pVertices[i]->pos().rx();
		auto prevy = pVertices[i]->pos().ry();
		pVertices[i]->setPos(prevx+localx, prevy+localy);
	}
	updateVerticesPolygon();
}

void PolygonItem::movePolygon(qreal scenex, qreal sceney)
{
	auto params = getParams();
	params.x = scenex;
	params.y = sceney;
	setParams(params);
}

PolygonItem::~PolygonItem()
{
}

QRectF PolygonItem::boundingRect() const
{
	return verticesPolygon.boundingRect();
}

void PolygonItem::updateVerticesPolygon()
{
	QPolygonF updatedPolygon;
	for (int i = 0; i<pVertices.size(); ++i)
	{
		updatedPolygon << this->mapFromItem((pVertices[i]),0,0);
	}
	updatedPolygon << this->mapFromItem((pVertices[0]),0,0); //closes polygon
	verticesPolygon = updatedPolygon;
}

void PolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(Qt::black);
	QBrush brush = QBrush(QColor(255,0,255,128));
	painter->setBrush(brush/*Qt::green*/);
	painter->drawPolygon(verticesPolygon);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString PolygonItem::getType()
{
	return QString("polygon");
}

polygonParams PolygonItem::getParams()
{
	return _params;
}

void PolygonItem::on_positionIsSet()
{
	auto params = _params;
	params.x = this->pos().toPoint().x();
	params.y = this->pos().toPoint().y();
	setParams(params);
}

void PolygonItem::setParams(polygonParams params)
{
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
}

void PolygonItem::bindVertexSignals(VertexItem *vertex)
{
	connect(vertex, SIGNAL(vertexMoved(VertexItem*)), this, SLOT(on_vertexMoved(VertexItem*)));
	connect(vertex, SIGNAL(vertexMoveFinished(VertexItem*)), this, SLOT(on_childVertexMoveFinished(VertexItem *)));
	connect(vertex, SIGNAL(vertexAskToClone(VertexItem*)), this, SLOT(on_vertexAskToClone(VertexItem*)));
	connect(vertex, SIGNAL(vertexDeleted(VertexItem*)), this, SLOT(on_vertexDeleted(VertexItem*)));
}

void PolygonItem::on_vertexMoved(VertexItem *movedVertex)
{
	updateVerticesPolygon();
	Q_UNUSED(movedVertex);
}

void PolygonItem::on_childVertexMoveFinished(VertexItem *movedVertex)
{
	auto pos = movedVertex->pos();
	if (pos.rx()<0 || pos.ry()<0)
		updatePolygonPosToTopLeftOfVerticesBoundingRect();
}

void PolygonItem::on_vertexAskToClone(VertexItem *clonedVertex)
{
	int i = -1;
	for (int j = 0; j<pVertices.size(); ++j)
	{
		/* FIXME: vertices are compared by their position (because '==' is deleted) */
		if (pVertices[j]->pos() == clonedVertex->pos())
			i = j;
	}
	if (i != -1)
	{
		VertexItem *newVertex = new VertexItem(this);
		/* TODO: case when clonedVertex is close to the border */
		QPointF clonedPos = clonedVertex->pos();
		newVertex->setPos(clonedPos.rx()-2, clonedPos.ry()-2);
		newVertex->setParentItem(this);
		pVertices.insert(i, newVertex);
		bindVertexSignals(newVertex);
		updateVerticesPolygon();
		this->update();
	}
}

void PolygonItem::on_vertexDeleted(VertexItem *deletedVertex)
{
	int i = -1;
	for (int j = 0; j<pVertices.size(); ++j)
	{
		/* FIXME: vertices are compared by their position (because '==' is deleted) */
		if (pVertices[j]->pos() == deletedVertex->pos())
			i = j;
	}
	if (i != -1)
	{
		if ((pVertices.size() == 1)&&(i == 0))
			this->scene()->removeItem(this);
		else
		{
			pVertices.remove(i);
			updateVerticesPolygon();
			this->update();
		}
	}
}

void PolygonItem::on_itemSelected(MoveItem *selectedItem)
{
	emit itemSelected(selectedItem);
}

void PolygonItem::on_itemDragged(MoveItem *draggedItem)
{
	emit itemDragged(draggedItem);
}

QRectF PolygonItem::getBoundingRect()
{
	return this->boundingRect();
}

/*QPointF PolygonItem::calculateValidCoordinates(QPointF newCoordinates)
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
*/
