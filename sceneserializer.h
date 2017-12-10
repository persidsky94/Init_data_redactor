#ifndef SCENESERIALIZER_H
#define SCENESERIALIZER_H

#include "gridscene.h"
#include "sceneitemcontainer.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"
#include <QDataStream>

class SceneSerializer: public QObject
{
	Q_OBJECT
public:
	SceneSerializer();
	void serializeSceneToFile(SceneItemContainer *container, QString filename);
	void deserializeFromFileToScene(GridScene *scene, QString filename);

signals:
	void addItemToScene(MoveItem *item);

private:
	void serializeSources(std::vector<SourceItem *> *sources, QDataStream& stream);
	void serializeRecievers(std::vector<RecieverGroup *> *recievers, QDataStream& stream);
	void serializePolygons(std::vector<PolygonItem *> *polygons, QDataStream& stream);
	void serializePolygonVertices(PolygonItem *polygon, QDataStream& stream);

	void serializeSingleSource(SourceItem *source, QDataStream& stream);
	void serializeSingleReciever(RecieverGroup *recieverGroup, QDataStream& stream);
	void serializeSinglePolygon(PolygonItem *polygon, QDataStream& stream);
	void serializePolygonParams(PolygonItem *polygon, QDataStream& stream);
	void serializeSingleVertex(VertexItem *vertex, QDataStream& stream);

	void deserializeSources(QDataStream& stream, GridScene *scene);
	void deserializeRecievers(QDataStream& stream, GridScene *scene);
	void deserializePolygons(QDataStream& stream, GridScene *scene);
	std::vector<VertexItem *> deserializePolygonVertices(QDataStream& stream);

	void deserializeSingleSource(QDataStream& stream, GridScene *scene);
	void deserializeSingleReciever(QDataStream& stream, GridScene *scene);
	void deserializeSinglePolygon(QDataStream& stream, GridScene *scene);
	polygonParams deserializePolygonParams(QDataStream& stream);
	VertexItem *deserializeSingleVertex(QDataStream& stream);

};

#endif // SCENESERIALIZER_H