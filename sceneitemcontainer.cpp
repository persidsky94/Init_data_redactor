#include "sceneitemcontainer.h"
#include <iostream>

SceneItemContainer::SceneItemContainer()
{
	_sources = new std::vector<SourceItem *>;
	_recievers = new std::vector<RecieverGroup *>;
	_polygons = new std::vector<PolygonItem *>;
}

SceneItemContainer::~SceneItemContainer()
{
	delete _sources;
	delete _recievers;
	delete _polygons;
}

void SceneItemContainer::clearContainer()
{
	_sources->clear();
	_recievers->clear();
	_polygons->clear();
	emit containerCleared();
}

void SceneItemContainer::addItemToContainer(MoveItem *itemToAdd)
{
	if(itemToAdd->getType() == QString("source"))
	{
		_sources->push_back(dynamic_cast<SourceItem *>(itemToAdd));
	}
	else if(itemToAdd->getType() == QString("reciever group"))
	{
		_recievers->push_back(dynamic_cast<RecieverGroup *>(itemToAdd));
	}
	else if(itemToAdd->getType() == QString("polygon"))
	{
		_polygons->push_back(dynamic_cast<PolygonItem *>(itemToAdd));
	}
	else
	{
		std::cout << "SceneItemContainer::addItemToContainer: unknown item type: " << itemToAdd->getType().toStdString() << std::endl;
	}
}

void SceneItemContainer::deleteItemFromContainer(MoveItem *itemToDelete)
{
	if(itemToDelete->getType() == QString("source"))
	{
		auto it = std::find(_sources->begin(), _sources->end(), dynamic_cast<SourceItem *>(itemToDelete));
		if(it != _sources->end())
			_sources->erase(it);
	}
	else if(itemToDelete->getType() == QString("reciever group"))
	{
		auto it = std::find(_recievers->begin(), _recievers->end(), dynamic_cast<RecieverGroup *>(itemToDelete));
		if(it != _recievers->end())
			_recievers->erase(it);
	}
	else if(itemToDelete->getType() == QString("polygon"))
	{
		auto it = std::find(_polygons->begin(), _polygons->end(), dynamic_cast<PolygonItem *>(itemToDelete));
		if(it != _polygons->end())
			_polygons->erase(it);
	}
	else
	{
		std::cout << "SceneItemContainer::deleteItemFromContainer: unknown item type: " << itemToDelete->getType().toStdString() << std::endl;
	}
}

std::vector<SourceItem *> *SceneItemContainer::getSceneSources()
{
	return _sources;
}

std::vector<RecieverGroup *> *SceneItemContainer::getSceneRecievers()
{
	return _recievers;
}

std::vector<PolygonItem *> *SceneItemContainer::getScenePolygons()
{
	return _polygons;
}
