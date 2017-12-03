#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include <QWidget>

#include <vertexparams.h>

namespace Ui {
class VertexInfo;
}

class VertexInfo : public QWidget
{
	Q_OBJECT

public:
	explicit VertexInfo(QWidget *parent = 0);
	~VertexInfo();
	void initWithParams(vertexParams params);
	vertexParams constructParams();

//for editor
	void updateParams(vertexParams params);

signals: //to item
	void setParams(vertexParams params);

private:
	Ui::VertexInfo *ui;

	void setMaxValues(QRectF sceneBR);

};

#endif // VERTEXINFO_H
