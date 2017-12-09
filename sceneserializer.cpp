#include "sceneserializer.h"
#include <QFile>

SceneSerializer::SceneSerializer()
{

}

void SceneSerializer::serializeSceneToFile(SceneItemContainer *container, QString filename)
{
	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	serializeSources(container->getSceneSources(), out);
	serializeRecievers(container->getSceneRecievers(), out);
	serializePolygons(container->getScenePolygons(), out);
}

void SceneSerializer::deserializeFromFileToScene(GridScene *scene, QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	deserializeSources(in, scene);
	deserializeRecievers(in, scene);
	deserializePolygons(in, scene);
}

void SceneSerializer::serializeSources(std::vector<SourceItem *> *sources, QDataStream &stream)
{
	stream << quint16(sources->size());
	for (auto &source: *sources)
	{
		serializeSingleSource(source, stream);
	}
}

void SceneSerializer::serializeRecievers(std::vector<RecieverGroup *> *recievers, QDataStream &stream)
{

}

void SceneSerializer::serializePolygons(std::vector<PolygonItem *> *polygons, QDataStream &stream)
{

}

void SceneSerializer::serializeSingleSource(SourceItem *source, QDataStream &stream)
{
	auto params = source->getParams();
	stream << params.name;
	stream << qint8(params.signalType);
	stream << params.x;
	stream << params.y;
}

void SceneSerializer::deserializeSources(QDataStream &stream, GridScene *scene)
{
	qint16 numSources;
	stream >> numSources;
	for (qint16 i=0; i < numSources; ++i)
	{
		deserializeSingleSource(scene, stream);
	}
}

void SceneSerializer::deserializeRecievers(QDataStream &stream, GridScene *scene)
{

}

void SceneSerializer::deserializePolygons(QDataStream &stream, GridScene *scene)
{

}

void SceneSerializer::deserializeSingleSource(GridScene *scene, QDataStream &stream)
{
	sourceParams params;
	stream >> params.name;
	qint8 type;
	stream >> type;
	params.signalType = sourceParams::SignalType(type);
	stream >> params.x;
	stream >> params.y;

	auto source = new SourceItem(params, scene);
	//scene->addItem(source);
	emit addItemToScene(source);
}
