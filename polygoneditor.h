#ifndef POLYGONEDITOR_H
#define POLYGONEDITOR_H

#include <QWidget>

#include <polygonparams.h>

namespace Ui {
class PolygonEditor;
}

class PolygonEditor : public QWidget
{
	Q_OBJECT

public:
	explicit PolygonEditor(QWidget *parent = 0);
	~PolygonEditor();
	void initWithParams(polygonParams params);
	polygonParams constructParams();

signals: //to item
	void setParams(polygonParams params);

private:
	Ui::PolygonEditor *ui;

	void setMaxValues(QRectF sceneBR);
//slots from item
	void updateParams(polygonParams params);
};

#endif // POLYGONEDITOR_H
