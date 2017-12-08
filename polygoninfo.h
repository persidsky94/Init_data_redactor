#ifndef POLYGONINFO_H
#define POLYGONINFO_H

#include <QWidget>

#include <polygonparams.h>

namespace Ui {
class PolygonInfo;
}

class PolygonInfo : public QWidget
{
	Q_OBJECT

public:
	explicit PolygonInfo(QWidget *parent = 0);
	~PolygonInfo();
	void initWithParams(polygonParams params);
	polygonParams constructParams();

//for editor
	void updateParams(polygonParams params);

signals: //to item
	void setParams(polygonParams params);

private:
	Ui::PolygonInfo *ui;

	void setMaxValues(QRectF sceneBR);
};

#endif // POLYGONINFO_H
