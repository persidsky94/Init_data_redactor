#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class GridScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GridScene(qreal x, qreal y, qreal w, qreal h);
	explicit GridScene(QObject *parent);
	~GridScene(){}

signals:
	void mouseAt(QPointF);

private:
	void setBackgroundGrid();
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRIDSCENE_H
