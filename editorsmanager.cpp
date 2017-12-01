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
	//recieverEditor = new RecieverGroupInfo(this->getWidget());
	//polygonEditor = new PolygonEditor(this->getWidget());
	auto layout = new QVBoxLayout();
	sourceEditor->addSelfToLayout(layout);
	//recieverEditor->addSelfToLayout(layout);
	//polygonEditor->addSelfToLayout(layout);
	sourceEditor->hide();
	//recieverEditor->hide();
	//polygonEditor->hide();
	_widget->setLayout(layout);
}

void EditorsManager::changeRedactedItem(MoveItem *newRedactedItem)
{
	unbindRedactedItem();
	hideActiveRedactor();
	setRedactedItem(newRedactedItem);
	bindRedactedItem();
	showActiveRedactor();
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
//TODO: add other item types
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
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
//TODO: add other item types
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
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
//TODO: add other item types
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
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
//TODO: add other item types
		else
		{
			std::cout << "Unknown MoveItem type selected" << std::endl;
		}
	}
}
