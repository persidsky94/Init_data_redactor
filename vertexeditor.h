#ifndef VERTEXEDITOR_H
#define VERTEXEDITOR_H

#include <QWidget>

#include <vertexparams.h>

namespace Ui {
class VertexEditor;
}

class VertexEditor : public QWidget
{
	Q_OBJECT

public:
	explicit VertexEditor(QWidget *parent = 0);
	~VertexEditor();
	void initWithParams(vertexParams params);
	vertexParams constructParams();

signals: //to item
	void setParams(vertexParams params);

private:
	Ui::VertexEditor *ui;

	void setMaxValues(QRectF sceneBR);
//slots from item
	void updateParams(vertexParams params);
};

#endif // VERTEXEDITOR_H
