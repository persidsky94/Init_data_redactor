#ifndef SCENEITEMCONTAINER_H
#define SCENEITEMCONTAINER_H

#include "moveitem.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"

class SceneItemContainer
{
public:
	SceneItemContainer();
	~SceneItemContainer();
	void addItemToContainer(MoveItem *itemToAdd);
	void deleteItemFromContainer(MoveItem *itemToDelete);
	std::vector<SourceItem *> *getSceneSources();
	std::vector<RecieverGroup *> *getSceneRecievers();
	std::vector<PolygonItem *> *getScenePolygons();

private:
	std::vector<SourceItem *> *_sources;
	std::vector<RecieverGroup *> *_recievers;
	std::vector<PolygonItem *> *_polygons;
};

#endif // SCENEITEMCONTAINER_H
