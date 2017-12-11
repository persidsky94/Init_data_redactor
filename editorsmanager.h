#ifndef EDITORSMANAGER_H
#define EDITORSMANAGER_H

#include <QObject>

#include <moveitem.h>
#include <sourceeditor.h>
#include <recievergroupeditor.h>
#include <polygoneditor.h>
#include <vertexinfo.h>
#include <polygoninfo.h>

class EditorsManager : public QObject
{
	Q_OBJECT
public:
	explicit EditorsManager(QWidget *parent = nullptr);
	QWidget *getWidget(){return _widget;}

	void changeRedactedItem(MoveItem *newRedactedItem);

	void on_sceneCleared();

private:
	MoveItem *redactedItem;
	QWidget *_widget;
	SourceEditor *sourceEditor;
	RecieverGroupEditor *recieverEditor;
	PolygonEditor *polygonEditor;

	void invalidateSelection();
	bool needToChangeRedactedItem(MoveItem *newRedactedItem);
	MoveItem *proxyNewRedactedItem(MoveItem *newRedactedItem);
	void unbindRedactedItem();
	void bindRedactedItem();
	void setRedactedItem(MoveItem *newItem);
	void hideActiveRedactor();
	void showActiveRedactor();
};

#endif // EDITORSMANAGER_H
