#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "sceneparams.h"
#include "moveitem.h"
#include "sceneitemcontainer.h"

class GridScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GridScene(sceneParams params ,QObject *parent);
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

	sceneParams getParams(){return _params;}
	void setParams(sceneParams params);


signals:
	void mouseAt(QPointF);
	void sceneItemSelected(MoveItem *);
	void sceneItemDeleted(MoveItem *);
	void sceneItemNameChanged(MoveItem *);

private:
	sceneParams _params;

	void setBackgroundGrid();
	void drawBorders();
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRIDSCENE_H
