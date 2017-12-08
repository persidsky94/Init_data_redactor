#ifndef ITEMLISTMANAGER_H
#define ITEMLISTMANAGER_H

#include <QObject>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <moveitem.h>
#include <polygonitem.h>

class ItemListManager : public QObject
{
	Q_OBJECT
public:
	explicit ItemListManager(QWidget *parent, bool needDuplicateButton);
	QWidget *getWidget(){return _widget;}
	void addSelfToLayout(QLayout *layout){layout->addWidget(_widget);}
	void parsePolygon(PolygonItem *polygon);
	void clearList();

signals:
	void deleteContainerItem(int containerItemIndex);
	void deleteContainerItemByPtr(MoveItem *containerItemToDelete);
	void selectContainerItem(MoveItem *containerItemToSelect);
	void duplicateContainerItem(int containerItemIndex);

public slots:
	void on_itemAddedToContainer(MoveItem *containerItem, int index);
	void on_itemDeletedFromContainer(MoveItem *containerItem);
	void on_itemSelectedInContainer(MoveItem *containerItem);

	void on_containerItemNameChanged(MoveItem *containerItem);

	//internal
	void on_duplicateButtonClicked();
	void on_deleteButtonClicked();
	void on_listItemSelected(QListWidgetItem *listItem);

private:
	MoveItem *selectedItem;
	QWidget *_widget;
	QListWidget *_listWidget;
	QPushButton *_duplicateButton;
	QPushButton *_deleteButton;
	const static int containerItemPtrRole = 1;

	void bindDuplicateButtonFunctions();
	void bindDeleteButtonFunction();
	void bindItemFromListSelection();
	QListWidgetItem *findListItemByContainerItemPointer(MoveItem *sceneItem);
	MoveItem *getContainerItemFromListItem(QListWidgetItem *listItem);
};

#endif // ITEMLISTMANAGER_H
