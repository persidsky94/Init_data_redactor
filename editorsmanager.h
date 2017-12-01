#ifndef EDITORSMANAGER_H
#define EDITORSMANAGER_H

#include <QObject>

#include <moveitem.h>
#include <sourceeditor.h>
#include <recievergroupinfo.h>
#include <vertexeditor.h>
#include <polygoneditor.h>

class EditorsManager : public QObject
{
	Q_OBJECT
public:
	explicit EditorsManager(QWidget *parent = nullptr);
	QWidget *getWidget(){return _widget;}

	void changeRedactedItem(MoveItem *newRedactedItem);

private:
	MoveItem *redactedItem;
	QWidget *_widget;
	SourceEditor *sourceEditor;
	RecieverGroupInfo *recieverEditor;
	PolygonEditor *polygonEditor;

	void unbindRedactedItem();
	void bindRedactedItem();
	void setRedactedItem(MoveItem *newItem);
	void hideActiveRedactor();
	void showActiveRedactor();
};

#endif // EDITORSMANAGER_H
