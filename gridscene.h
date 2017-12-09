#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "moveitem.h"
#include "sceneitemcontainer.h"

class GridScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GridScene(qreal x, qreal y, qreal w, qreal h);
	explicit GridScene(QObject *parent);
	~GridScene(){}

	//slots from items
	void on_sceneItemSelected(MoveItem *);
	void on_itemNameChanged(MoveItem *);
	//slots from item list manager
	void on_selectSceneItem(MoveItem *);
	void on_deleteSceneItem(MoveItem *);

	//for item container interactions
	void addItem(QGraphicsItem *item);
	void removeItem(QGraphicsItem *item);

	SceneItemContainer *getItemContainer(){return &_itemContainer;}


signals:
	void mouseAt(QPointF);
	void sceneItemSelected(MoveItem *);
	void sceneItemDeleted(MoveItem *);
	void sceneItemNameChanged(MoveItem *);

private:
	SceneItemContainer _itemContainer;

	void setBackgroundGrid();
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRIDSCENE_H
