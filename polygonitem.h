#ifndef POLYGONITEM_H
#define POLYGONITEM_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPolygon>


#include <moveitem.h>
#include <vertexitem.h>

class PolygonItem : public MoveItem
{
	Q_OBJECT
public:
	explicit PolygonItem(QObject *parent = 0);
	~PolygonItem();
	QRectF getBoundingRect();

private slots:
	void on_vertexMoved(VertexItem *);
	void on_vertexAskToClone(VertexItem *);
	void on_vertexDeleted(VertexItem *);

	void on_itemSelected(MoveItem *);
	void on_itemDragged(MoveItem *);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();

	QPointF calculateValidCoordinates(QPointF newCoordinates);

	void updateVerticesPolygon();
	void bindVertexSignals(VertexItem *);

	int density = 1000;
	QVector<VertexItem *> pVertices;
	QPolygonF verticesPolygon;
};

#endif // POLYGONITEM_H
