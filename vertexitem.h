#ifndef VERTEXITEM_H
#define VERTEXITEM_H

#include <QObject>
#include <QString>

#include <moveitem.h>
#include <vertexparams.h>

class VertexItem : public MoveItem
{
	Q_OBJECT
public:
	explicit VertexItem(vertexParams params, QObject *parent = 0);
	~VertexItem();
	vertexParams getParams();
	void setParams(vertexParams params);
	QString getName() {return getParams().name;}

signals:
	void vertexMoved(VertexItem *);
	void vertexMoveFinished(VertexItem *);
	void vertexAskToClone(VertexItem *);
	void vertexDeleted(VertexItem *);

	void paramsChanged(vertexParams params);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
	void on_positionIsSet();

	void mouseMoveEvent(QGraphicsSceneMouseEvent *);
	void mousePressEvent(QGraphicsSceneMouseEvent *);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	vertexParams _params;
};

#endif // VERTEXITEM_H
