#ifndef SCENEITEMCONTAINER_H
#define SCENEITEMCONTAINER_H

#include <QObject>
#include "moveitem.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"

class SceneItemContainer: public QObject
{
	Q_OBJECT
public:
	SceneItemContainer();
	~SceneItemContainer();
	void addItemToContainer(MoveItem *itemToAdd);
	void deleteItemFromContainer(MoveItem *itemToDelete);
	void clearContainer();
	std::vector<SourceItem *> *getSceneSources();
	std::vector<RecieverGroup *> *getSceneRecievers();
	std::vector<PolygonItem *> *getScenePolygons();

signals:
	void containerCleared();

private:
	std::vector<SourceItem *> *_sources;
	std::vector<RecieverGroup *> *_recievers;
	std::vector<PolygonItem *> *_polygons;
};

#endif // SCENEITEMCONTAINER_H
