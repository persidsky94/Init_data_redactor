#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include "gridscene.h"
#include "moveitem.h"
#include "sceneserializer.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"

class SceneManager : public QObject
{
	Q_OBJECT
public:
	explicit SceneManager(QObject *parent = nullptr);

	void addNewSourceItem(sourceParams params);
	void addNewRecieverItem(recieverGroupParams params);
	void addNewPolygonItem(polygonParams params);
	void removeItemFromScene(MoveItem *itemToRemove);
	void clearScene();
	void serializeSceneToFile();
	void deserializeSceneFromFile();
	void changeSceneSettings();


	GridScene *getScene(){return _scene;}
	SceneItemContainer *getItemContainer(){return _itemContainer;}

	sourceParams getDefaultSourceParams(){return _defaultSourceParams;}
	recieverGroupParams getDefaultRecieverGroupParams(){return _defaultRecieverGroupParams;}
	polygonParams getDefaultPolygonParams(){return _defaultPolygonParams;}

signals:
	//for list manager
	void itemAddedToScene(MoveItem *addedItem, int index);
	void itemRemovedFromScene(MoveItem *removedItem);

	//from scene to whoever wants it
	void sceneItemSelected(MoveItem *item);
	void sceneItemDeleted(MoveItem *item);
	void sceneItemNameChanged(MoveItem *item);
	//for scene from anyone
	void selectSceneItem(MoveItem *item);

	void sceneCleared();

public slots:

private:
	GridScene *_scene;
	SceneItemContainer *_itemContainer;
	SceneSerializer *_serializer;

	sceneParams _defaultSceneParams;
	sourceParams _defaultSourceParams;
	recieverGroupParams _defaultRecieverGroupParams;
	polygonParams _defaultPolygonParams;

	void addItemToScene(MoveItem *itemToAdd);
	void bindItemToScene(MoveItem *item);

	sceneParams getSceneParams();

	void doTheBindings();
	void bindSceneToSelf();
	void bindSerializerToSelf();

	void setSceneParams(sceneParams params);

	void setDefaultItemsParams();
	void setDefaultSceneParams();
	void setDefaultSourceParams();
	void setDefaultRecieverGroupParams();
	void setDefaultPolygonParams();
};

#endif // SCENEMANAGER_H
