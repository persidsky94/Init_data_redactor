#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPolygon>


#include <moveitem.h>
#include <polygonparams.h>
#include <vertexparams.h>
#include <vertexitem.h>

class PolygonItem : public MoveItem
{
	Q_OBJECT
public:
	explicit PolygonItem(polygonParams params, QObject *parent = 0);
	~PolygonItem();
	polygonParams getParams();
	void setParams(polygonParams params);
	QString getName() {return getParams().name;}
	QRectF getBoundingRect();

signals:
	void paramsChanged(polygonParams params);
	void childVertexParamsChanged(vertexParams params);
	void childVertexCreated(PolygonItem *polygon, VertexItem *vertex);
	void childVertexDeleted(VertexItem *vertex);

private slots:
	void on_vertexMoved(VertexItem *);
	void on_childVertexMoveFinished(VertexItem *);
	void on_vertexAskToClone(VertexItem *);
	void on_vertexDeleted(VertexItem *);

	void on_itemSelected(MoveItem *);
	void on_itemDragged(MoveItem *);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
	void on_positionIsSet();

	void setDefaultVertexParams();

//	QPointF calculateValidCoordinates(QPointF newCoordinates);
	VertexItem *createChildVertex(int index, qreal localx, qreal localy);
	void moveAllVertecesBy(qreal x, qreal y);
	void movePolygon(qreal scenex, qreal sceney);
	void updatePolygonPosToTopLeftOfVerticesBoundingRect();

	void updateVerticesPolygon();
	void bindVertexSignals(VertexItem *);

	polygonParams _params;
	vertexParams _defaultVertexParams;
	QVector<VertexItem *> pVertices;
	QPolygonF verticesPolygon;
};

#endif // POLYGONITEM_H
