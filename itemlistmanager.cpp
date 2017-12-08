#include "itemlistmanager.h"
#include <QVBoxLayout>

ItemListManager::ItemListManager(QWidget *parent, bool needDuplicateButton) : QObject(parent)
{
	_widget = new QWidget(parent);
	_listWidget = new QListWidget();
	_deleteButton = new QPushButton(QString("delete"));
	auto layout = new QVBoxLayout;
	layout->addWidget(_listWidget);
	if (needDuplicateButton)
	{
		_duplicateButton = new QPushButton(QString("duplicate"));
		layout->addWidget(_duplicateButton);
		bindDuplicateButtonFunctions();
	}
	layout->addWidget(_deleteButton);
	_listWidget->show();
	_widget->setLayout(layout);
	bindDeleteButtonFunction();
	bindItemFromListSelection();
}

void ItemListManager::parsePolygon(PolygonItem *polygon)
{
	clearList();
	auto vertNumber = polygon->pVertices.size();
	for (int i = vertNumber - 1; i >= 0; --i)
	{
		on_itemAddedToContainer(polygon->pVertices[i], 0);
	}
}

void ItemListManager::clearList()
{
	_listWidget->clear();
}

void ItemListManager::on_itemAddedToContainer(MoveItem *containerItem, int index)
{
	auto listItem = new QListWidgetItem();
	listItem->setText(containerItem->getName());
	QVariant listItemData = qVariantFromValue((void *) containerItem);
	listItem->setData(containerItemPtrRole, listItemData);
	_listWidget->insertItem(index, listItem);
}

void ItemListManager::on_itemDeletedFromContainer(MoveItem *containerItem)
{
	auto listItem = findListItemByContainerItemPointer(containerItem);
	auto row =_listWidget->row(listItem);
	auto removedItem = _listWidget->takeItem(row);
}

void ItemListManager::on_itemSelectedInContainer(MoveItem *containerItem)
{
	auto listItem = findListItemByContainerItemPointer(containerItem);
	if (listItem)
	{
		_listWidget->setCurrentItem(listItem);
		listItem->setSelected(1);
	}
}

void ItemListManager::on_containerItemNameChanged(MoveItem *containerItem)
{
	auto listItem = findListItemByContainerItemPointer(containerItem);
	listItem->setText(containerItem->getName());
}

QListWidgetItem *ItemListManager::findListItemByContainerItemPointer(MoveItem *sceneItem)
{
	auto listItemsNumber = _listWidget->count();
	QListWidgetItem *listItem = NULL;
	for (int i=0; i<listItemsNumber; ++i)
	{
		listItem = _listWidget->item(i);
		auto sceneItemFromListItem = getContainerItemFromListItem(listItem);
		if (sceneItemFromListItem == sceneItem)
			return listItem;
	}
	return NULL;
}

MoveItem *ItemListManager::getContainerItemFromListItem(QListWidgetItem *listItem)
{
	return (MoveItem *)(listItem->data(containerItemPtrRole).value<void *>());
}

void ItemListManager::on_duplicateButtonClicked()
{
	emit duplicateContainerItem(_listWidget->currentRow());
}

void ItemListManager::on_deleteButtonClicked()
{
	auto listItem = _listWidget->currentItem();
	auto sceneItem = getContainerItemFromListItem(listItem);
	emit deleteContainerItemByPtr(sceneItem);
	emit deleteContainerItem(_listWidget->currentRow());
}

void ItemListManager::on_listItemSelected(QListWidgetItem *listItem)
{
	auto sceneItem = getContainerItemFromListItem(listItem);
	emit selectContainerItem(sceneItem);
}

void ItemListManager::bindDuplicateButtonFunctions()
{
	QObject::connect(_duplicateButton, &QPushButton::clicked, this, &ItemListManager::on_duplicateButtonClicked);
}
void ItemListManager::bindDeleteButtonFunction()
{
	QObject::connect(_deleteButton, &QPushButton::clicked, this, &ItemListManager::on_deleteButtonClicked);
}
void ItemListManager::bindItemFromListSelection()
{
	QObject::connect(_listWidget, &QListWidget::itemClicked, this, &ItemListManager::on_listItemSelected);
}
