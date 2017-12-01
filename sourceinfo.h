#ifndef SourceInfo_H
#define SourceInfo_H

#include <QWidget>

#include <sourceparams.h>

namespace Ui {
class SourceInfo;
}

class SourceInfo : public QWidget
{
	Q_OBJECT

public:
	explicit SourceInfo(QWidget *parent = 0);
	~SourceInfo();
	void initWithParams(sourceParams params);
	sourceParams constructParams();

	//for editor
	void updateParams(sourceParams params);

//signals: //to item
//	void setParams(sourceParams params);

private:
	Ui::SourceInfo *ui;

	void setBoxEnums();
	void setMaxValues(QRectF sceneBR);

};

#endif // SourceInfo_H
