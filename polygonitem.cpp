#include "polygonitem.h"

PolygonItem::PolygonItem(QObject *parent)
	: MoveItem(parent)
{
	this->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
	QPointF pos = QPointF(200,200);
	this->setPos(pos);
	VertexItem *firstVertex = new VertexItem(this);
	firstVertex->setPos(0,0);
	firstVertex->setParentItem(this);
	pVertices.append(firstVertex);
	topVertex = botVertex = leftVertex = rightVertex = firstVertex;
	bindVertexSignals(firstVertex);
	updateVerticesPolygon();
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
	updatedPolygon << this->mapFromItem((pVertices[0]),0,0);
	verticesPolygon = updatedPolygon;
}

void PolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//painter->setBrush(Qt::red);
//painter->drawRect(this->getBoundingRect());
	painter->setPen(Qt::black);
	QBrush brush = QBrush(QColor(255,0,255,128));
	painter->setBrush(brush/*Qt::green*/);
	painter->drawPolygon(verticesPolygon);
//painter->drawEllipse(0,0,6,6);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QString PolygonItem::getType()
{
	return QString("Polygon");
}

void PolygonItem::bindVertexSignals(VertexItem *vertex)
{
	connect(vertex, SIGNAL(vertexMoved(VertexItem*)), this, SLOT(on_vertexMoved(VertexItem*)));
	connect(vertex, SIGNAL(vertexAskToClone(VertexItem*)), this, SLOT(on_vertexAskToClone(VertexItem*)));
	connect(vertex, SIGNAL(vertexDeleted(VertexItem*)), this, SLOT(on_vertexDeleted(VertexItem*)));
}

void PolygonItem::on_vertexMoved(VertexItem *movedVertex)
{
	updateVerticesPolygon();
	Q_UNUSED(movedVertex);
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

QPointF PolygonItem::calculateValidCoordinates(QPointF newCoordinates)
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
