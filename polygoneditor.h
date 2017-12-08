#ifndef POLYGONEDITOR_H
#define POLYGONEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

#include "polygoninfo.h"
#include "polygonitem.h"
#include "vertexeditor.h"
#include "vertexitem.h"
#include "itemlistmanager.h"

class PolygonEditor : public QObject
{
	Q_OBJECT
public:
	explicit PolygonEditor(QWidget *parent = nullptr);
	~PolygonEditor();
	void addSelfToLayout(QLayout *layout);
	void initWithParams(polygonParams params);
	void makeVertexListManagerCorrespondingToPolygonItem(PolygonItem *polygon);
	void show();
	void hide();

	void initVertexEditorWithParams(vertexParams params);

	void bindVertexListManagerToSelf();
	void rebindVertexEditor(MoveItem *newRedactedVertex);

	void bindVertexListManagerToPolygon(PolygonItem *polygon);
	void unbindVertexListManagerFromEverything();

	void bindVertexEditorToVertex(VertexItem *vertex);
	void unbindVertexEditorFromEverything();

signals:
	void setParams(polygonParams params);

private:
	QWidget *_widget;
	PolygonInfo *_polygonParamsInfo;
	ItemListManager *_vertexListManager;
	VertexEditor *_vertexEditor;
	QPushButton *_setPolygonParamsButton;

	void clearVertexListManager();

//slots from item
	void updateParams(polygonParams params);
//slots from ui
	void on_setButton_clicked();
};

#endif // POLYGONEDITOR_H
