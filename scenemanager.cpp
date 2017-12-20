#include "scenemanager.h"
#include "sceneinfo.h"
#include <QFile>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>

SceneManager::SceneManager(QObject *parent) : QObject(parent)
{
	setDefaultItemsParams();
	_scene = new GridScene(_defaultSceneParams ,this);
	_itemContainer = new SceneItemContainer();
	_serializer = new SceneSerializer();
    _converter = new ToInitDataConverter(_itemContainer, _scene);
	doTheBindings();
}

void SceneManager::addNewSourceItem(sourceParams params)
{
	auto src = new SourceItem(params, this);
	addItemToScene(src);
	src->itemSelected(src);
}

void SceneManager::addNewRecieverItem(recieverGroupParams params)
{
	auto recv = new RecieverGroup(params, this);
	addItemToScene(recv);
	recv->itemSelected(recv);
}

void SceneManager::addNewPolygonItem(polygonParams params)
{
	auto poly = new PolygonItem(params, this);
	addItemToScene(poly);
	poly->itemSelected(poly);
}

void SceneManager::addItemToScene(MoveItem *item)
{
	_scene->addItem(item);
	bindItemToScene(item);
	_itemContainer->addItemToContainer(item);
	emit itemAddedToScene(item, 0);
}

void SceneManager::bindItemToScene(MoveItem *item)
{
	QObject::connect(item, &MoveItem::itemSelected, _scene, &GridScene::on_sceneItemSelected);
	QObject::connect(item, &MoveItem::nameChanged, _scene, &GridScene::on_itemNameChanged);
}

void SceneManager::removeItemFromScene(MoveItem *itemToRemove)
{
	_itemContainer->deleteItemFromContainer(dynamic_cast<MoveItem *>(itemToRemove));
	emit itemRemovedFromScene(itemToRemove);
	_scene->removeItem(itemToRemove);
}

void SceneManager::clearScene()
{
	_itemContainer->clearContainer();
	_scene->clear();
	emit sceneCleared();
}

void SceneManager::serializeSceneToFile()
{
	auto filename = QFileDialog::getSaveFileName(NULL, "Choose where to save model", QDir::currentPath());
	QFile::remove(filename);
	_serializer->serializeSceneToFile(_itemContainer, filename);
}

void SceneManager::deserializeSceneFromFile()
{
	clearScene();
	auto filename = QFileDialog::getOpenFileName(NULL, "Choose from where to load model", QDir::currentPath());
	_serializer->deserializeFromFileToScene(_scene, filename);
}

void SceneManager::convertToInitData()
{
    _converter->convertToInitData();
}

void SceneManager::changeSceneSettings()
{
	auto dialog = new QDialog;
	auto layout = new QVBoxLayout(dialog);
	auto sceneInfo = new SceneInfo(dialog);
	sceneInfo->initWithParams(getSceneParams());
	sceneInfo->show();
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
	layout->addWidget(sceneInfo);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
	if (dialog->exec())
	{
		auto params = sceneInfo->constructParams();
		setSceneParams(params);
	}
	delete dialog;
}

sceneParams SceneManager::getSceneParams()
{
	return _scene->getParams();
}

void SceneManager::setSceneParams(sceneParams params)
{
	_scene->setParams(params);
}

void SceneManager::doTheBindings()
{
	bindSceneToSelf();
	bindSerializerToSelf();
}

void SceneManager::bindSerializerToSelf()
{
	QObject::connect(_serializer, &SceneSerializer::addItemToScene, this, &SceneManager::addItemToScene);
}

void SceneManager::bindSceneToSelf()
{
	QObject::connect(_scene, &GridScene::sceneItemSelected, this, &SceneManager::sceneItemSelected);
	QObject::connect(_scene, &GridScene::sceneItemDeleted, this, &SceneManager::sceneItemDeleted);
	QObject::connect(_scene, &GridScene::sceneItemNameChanged, this, &SceneManager::sceneItemNameChanged);
	QObject::connect(this, &SceneManager::selectSceneItem, _scene, &GridScene::on_selectSceneItem);
}

void SceneManager::setDefaultItemsParams()
{
	setDefaultSceneParams();
	setDefaultSourceParams();
	setDefaultRecieverGroupParams();
	setDefaultPolygonParams();
}

void SceneManager::setDefaultSceneParams()
{
	_defaultSceneParams.name = QString("Scene");
    _defaultSceneParams.nodes_x = 300;
    _defaultSceneParams.nodes_y = 300;
    _defaultSceneParams.space_step_x = 1.0;
    _defaultSceneParams.space_step_y = 1.0;
    _defaultSceneParams.time_steps = 2000;
    _defaultSceneParams.time_step = 0.00005;
    _defaultSceneParams.save_step = 10;
    _defaultSceneParams.density = 1.0;
    _defaultSceneParams.speed_c = 1000.0;
    _defaultSceneParams.pml_length = 10;
    _defaultSceneParams.pml_maxvalue = 100.0;
}

void SceneManager::setDefaultSourceParams()
{
	_defaultSourceParams.name = QString("Source");
	_defaultSourceParams.x = 0;
	_defaultSourceParams.y = 0;
	_defaultSourceParams.signalType = sourceParams::Sin;
}

void SceneManager::setDefaultRecieverGroupParams()
{
	_defaultRecieverGroupParams.name = QString("Recievers group");
	_defaultRecieverGroupParams.firstx = 0;
	_defaultRecieverGroupParams.deltax = 30;
	_defaultRecieverGroupParams.y = 100;
	_defaultRecieverGroupParams.recieversNumber = 20;
}

void SceneManager::setDefaultPolygonParams()
{
	_defaultPolygonParams.name = QString("Polygon");
    _defaultPolygonParams.density = 1;
	_defaultPolygonParams.x = 30;
	_defaultPolygonParams.y = 30;
}
