#include "sceneserializer.h"
#include <QFile>
#include <QMessageBox>
#include <iostream>

SceneSerializer::SceneSerializer()
{

}

void SceneSerializer::serializeSceneToFile(SceneItemContainer *container, QString filename)
{
    QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	serializeSerializerVersion(out);
	serializeSources(container->getSceneSources(), out);
	serializeRecievers(container->getSceneRecievers(), out);
	serializePolygons(container->getScenePolygons(), out);
}

void SceneSerializer::deserializeFromFileToScene(GridScene *scene, QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	if (!deserializeSerializerVersion(in))
	{
		QMessageBox msgBox;
		auto text = QString("Serializer version incompatible, current version is %1").arg(serializerVersion);
		msgBox.setText(text);
		msgBox.exec();
		//std::cout << "Serializer version incompatible, current version is " << serializerVersion << endl;
		return;
	}
	deserializeSources(in, scene);
	deserializeRecievers(in, scene);
	deserializePolygons(in, scene);
}

void SceneSerializer::serializeSerializerVersion(QDataStream &stream)
{
	stream << qint16(serializerVersion);
}

bool SceneSerializer::deserializeSerializerVersion(QDataStream &stream)
{
	qint16 version;
	stream >> version;
	if ((int)version == serializerVersion)
		return true;
	else
		return false;
}

void SceneSerializer::serializeSceneParams(GridScene *scene, QDataStream &stream)
{
    auto params = scene->getParams();
    stream << params.name;
    stream << params.nodes_x;
    stream << params.nodes_y;
    stream << params.space_step_x;
    stream << params.space_step_y;
    stream << params.time_steps;
    stream << params.time_step;
    stream << params.save_step;
    stream << params.density;
    stream << params.speed_c;
    stream << params.pml_length;
    stream << params.pml_maxvalue;
}

void SceneSerializer::deserializeSceneParams(QDataStream &stream, GridScene *scene)
{
    sceneParams params;
    stream >> params.name;
    stream >> params.nodes_x;
    stream >> params.nodes_y;
    stream >> params.space_step_x;
    stream >> params.space_step_y;
    stream >> params.time_steps;
    stream >> params.time_step;
    stream >> params.save_step;
    stream >> params.density;
    stream >> params.speed_c;
    stream >> params.pml_length;
    stream >> params.pml_maxvalue;
    scene->setParams(params);
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
	stream << quint16(recievers->size());
	for (auto &reciever: *recievers)
	{
		serializeSingleReciever(reciever, stream);
	}
}

void SceneSerializer::serializePolygons(std::vector<PolygonItem *> *polygons, QDataStream &stream)
{
	stream << quint16(polygons->size());
	for (auto &polygon: *polygons)
	{
		serializeSinglePolygon(polygon, stream);
	}
}

void SceneSerializer::serializePolygonVertices(PolygonItem *polygon, QDataStream &stream)
{
	auto vertices = polygon->getVertices();
	stream << quint16(vertices.size());
	for (auto &vertex: vertices)
	{
		serializeSingleVertex(vertex, stream);
	}
}

void SceneSerializer::serializeSingleSource(SourceItem *source, QDataStream &stream)
{
	auto params = source->getParams();
	stream << params.name;
	stream << qint8(params.signalType);
	stream << params.x;
	stream << params.y;
}

void SceneSerializer::serializeSingleReciever(RecieverGroup *recieverGroup, QDataStream &stream)
{
	auto params = recieverGroup->getParams();
	stream << params.name;
	stream << params.recieversNumber;
	stream << params.deltax;
	stream << params.firstx;
	stream << params.y;
}

void SceneSerializer::serializeSinglePolygon(PolygonItem *polygon, QDataStream &stream)
{
	serializePolygonParams(polygon, stream);
	serializePolygonVertices(polygon, stream);
}

void SceneSerializer::serializePolygonParams(PolygonItem *polygon, QDataStream &stream)
{
	auto params = polygon->getParams();
	stream << params.name;
	stream << params.density;
    stream << params.speed_c;
	stream << params.x;
	stream << params.y;
}

void SceneSerializer::serializeSingleVertex(VertexItem *vertex, QDataStream &stream)
{
	auto params = vertex->getParams();
	stream << params.name;
	stream << params.x;
	stream << params.y;
}

void SceneSerializer::deserializeSources(QDataStream &stream, GridScene *scene)
{
	qint16 numSources;
	stream >> numSources;
	for (qint16 i=0; i < numSources; ++i)
	{
		deserializeSingleSource(stream, scene);
	}
}

void SceneSerializer::deserializeRecievers(QDataStream &stream, GridScene *scene)
{
	qint16 numRecievers;
	stream >> numRecievers;
	for (qint16 i=0; i < numRecievers; ++i)
	{
		deserializeSingleReciever(stream, scene);
	}
}

void SceneSerializer::deserializePolygons(QDataStream &stream, GridScene *scene)
{
	qint16 numPolygons;
	stream >> numPolygons;
	for (qint16 i=0; i < numPolygons; ++i)
	{
		deserializeSinglePolygon(stream, scene);
	}
}

std::vector<VertexItem *> SceneSerializer::deserializePolygonVertices(QDataStream &stream)
{
	qint16 numVertices;
	stream >> numVertices;
	std::vector<VertexItem *> vertices;
	for (qint16 i=0; i < numVertices; ++i)
	{
		auto vertex = deserializeSingleVertex(stream);
		vertices.push_back(vertex);
	}
	return vertices;
}

void SceneSerializer::deserializeSingleSource(QDataStream &stream, GridScene *scene)
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

void SceneSerializer::deserializeSingleReciever(QDataStream &stream, GridScene *scene)
{
	recieverGroupParams params;
	stream >> params.name;
	stream >> params.recieversNumber;
	stream >> params.deltax;
	stream >> params.firstx;
	stream >> params.y;

	auto reciever = new RecieverGroup(params, scene);
	//scene->addItem(source);
	emit addItemToScene(reciever);
}

void SceneSerializer::deserializeSinglePolygon(QDataStream &stream, GridScene *scene)
{
	auto params = deserializePolygonParams(stream);
	auto vertices = deserializePolygonVertices(stream);
	auto polygon = new PolygonItem(params, vertices, scene);
	emit addItemToScene(polygon);
}

polygonParams SceneSerializer::deserializePolygonParams(QDataStream &stream)
{
	polygonParams params;
	stream >> params.name;
	stream >> params.density;
    stream >> params.speed_c;
	stream >> params.x;
	stream >> params.y;
	return params;
}

VertexItem *SceneSerializer::deserializeSingleVertex(QDataStream &stream)
{
	vertexParams params;
	stream >> params.name;
	stream >> params.x;
	stream >> params.y;

	auto vertex = new VertexItem(params);
	return vertex;
}
