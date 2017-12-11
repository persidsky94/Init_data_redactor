#ifndef SCENEINFO_H
#define SCENEINFO_H

#include <QWidget>

#include <sceneparams.h>

namespace Ui {
class SceneInfo;
}

class SceneInfo : public QWidget
{
	Q_OBJECT

public:
	explicit SceneInfo(QWidget *parent = 0);
	~SceneInfo();
	void initWithParams(sceneParams params);
	sceneParams constructParams();

private:
	Ui::SceneInfo *ui;

//	void setMaxValues(QRectF sceneBR);
};

#endif // SCENEINFO_H
