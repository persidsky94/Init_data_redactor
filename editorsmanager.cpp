#include "editorsmanager.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"
#include <iostream>
#include <QVBoxLayout>

EditorsManager::EditorsManager(QWidget *parent) : QObject(parent)
{
	_widget = new QWidget(parent);
	_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	redactedItem = NULL;
	sourceEditor = new SourceEditor(this->getWidget());
	recieverEditor = new RecieverGroupEditor(this->getWidget());
	polygonEditor = new PolygonEditor(this->getWidget());
	auto layout = new QVBoxLayout();
	sourceEditor->addSelfToLayout(layout);
	recieverEditor->addSelfToLayout(layout);
	polygonEditor->addSelfToLayout(layout);
	sourceEditor->hide();
	recieverEditor->hide();
	polygonEditor->hide();
	_widget->setLayout(layout);
}

void EditorsManager::changeRedactedItem(MoveItem *newRedactedItem)
{
	auto proxiedNewRedactedItem = proxyNewRedactedItem(newRedactedItem);
	if (needToChangeRedactedItem(proxiedNewRedactedItem))
	{
		unbindRedactedItem();
		hideActiveRedactor();
		setRedactedItem(proxiedNewRedactedItem);
		bindRedactedItem();
		showActiveRedactor();
	}
}

MoveItem *EditorsManager::proxyNewRedactedItem(MoveItem *newRedactedItem)
{
	if (newRedactedItem->getType() == QString("vertex"))
	{
		if (newRedactedItem->parent() == redactedItem)
		{
			polygonEditor->unbindVertexEditorFromEverything();
			polygonEditor->bindVertexEditorToVertex(dynamic_cast<VertexItem *>(newRedactedItem));
			polygonEditor->initVertexEditorWithParams(dynamic_cast<VertexItem *>(newRedactedItem)->getParams());
		}
		return  dynamic_cast<MoveItem *>(newRedactedItem->parent());
	}
	else
		return newRedactedItem;
}

bool EditorsManager::needToChangeRedactedItem(MoveItem *newRedactedItem)
{
	if (newRedactedItem == redactedItem)
		return false;
	else
		return true;
}

void EditorsManager::setRedactedItem(MoveItem *newItem)
{
	redactedItem = newItem;
}

void EditorsManager::hideActiveRedactor()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("source"))
		{
			sourceEditor->hide();
		}
		else if (redactedItem->getType() == QString("reciever group"))
		{
			recieverEditor->hide();
		}
		else if(redactedItem->getType() == QString("polygon"))
		{
			polygonEditor->hide();
		}
		else
		{
			std::cout << " EditorsManager::showActiveRedactor: " << "Unknown MoveItem type selected: " << redactedItem->getType().toStdString() << std::endl;
		}
	}
}

void EditorsManager::showActiveRedactor()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("source"))
		{
			sourceEditor->show();
		}
		else if (redactedItem->getType() == QString("reciever group"))
		{
			recieverEditor->show();
		}
		else if(redactedItem->getType() == QString("polygon"))
		{
			polygonEditor->show();
		}
		else
		{
			std::cout << " EditorsManager::showActiveRedactor: " << "Unknown MoveItem type selected: " << redactedItem->getType().toStdString() << std::endl;
		}
	}
}

void EditorsManager::unbindRedactedItem()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("source"))
		{
			QObject::disconnect(sourceEditor, 0, 0, 0);
		}
		else if (redactedItem->getType() == QString("reciever group"))
		{
			QObject::disconnect(recieverEditor, 0, 0, 0);
		}
		else if(redactedItem->getType() == QString("polygon"))
		{
			polygonEditor->unbindVertexEditorFromEverything();
			polygonEditor->unbindVertexListManagerFromEverything();
			QObject::disconnect(polygonEditor, 0, 0, 0);
		}
		else
		{
			std::cout << " EditorsManager::unbindRedactedItem: " << "Unknown MoveItem type selected: " << redactedItem->getType().toStdString() << std::endl;
		}
	}
}

void EditorsManager::bindRedactedItem()
{
	if (redactedItem)
	{
		if (redactedItem->getType() == QString("source"))
		{
			SourceItem *srcItem = dynamic_cast<SourceItem *>(redactedItem);
			QObject::connect(srcItem, &SourceItem::paramsChanged, sourceEditor, &SourceEditor::initWithParams);
			QObject::connect(sourceEditor, &SourceEditor::setParams, srcItem, &SourceItem::setParams);
			sourceEditor->initWithParams(srcItem->getParams());
		}
		else if (redactedItem->getType() == QString("reciever group"))
		{
			RecieverGroup *rcvItem = dynamic_cast<RecieverGroup *>(redactedItem);
			QObject::connect(rcvItem, &RecieverGroup::paramsChanged, recieverEditor, &RecieverGroupEditor::initWithParams);
			QObject::connect(recieverEditor, &RecieverGroupEditor::setParams, rcvItem, &RecieverGroup::setParams);
			recieverEditor->initWithParams(rcvItem->getParams());
		}
		else if(redactedItem->getType() == QString("polygon"))
		{
			PolygonItem *polyItem = dynamic_cast<PolygonItem *>(redactedItem);
			QObject::connect(polyItem, &PolygonItem::paramsChanged, polygonEditor, &PolygonEditor::initWithParams);
			QObject::connect(polygonEditor, &PolygonEditor::setParams, polyItem, &PolygonItem::setParams);
			polygonEditor->makeVertexListManagerCorrespondingToPolygonItem(polyItem);
			polygonEditor->bindVertexListManagerToSelf();
			polygonEditor->bindVertexListManagerToPolygon(polyItem);
			polygonEditor->initWithParams(polyItem->getParams());
		}
		else
		{
			std::cout << " EditorsManager::bindRedactedItem: " << "Unknown MoveItem type selected: " << redactedItem->getType().toStdString() << std::endl;
		}
	}
}
