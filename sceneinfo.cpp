#include "sceneinfo.h"
#include "ui_sceneinfo.h"

SceneInfo::SceneInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneInfo)
{
	ui->setupUi(this);
}

SceneInfo::~SceneInfo()
{
	delete ui;
}

void SceneInfo::initWithParams(sceneParams params)
{
	ui->nameLine->setText(params.name);
	ui->widthBox->setValue(params.width);
	ui->heightBox->setValue(params.height);
}

sceneParams SceneInfo::constructParams()
{
	sceneParams params;
	params.name = ui->nameLine->text();
	params.width = ui->widthBox->value();
	params.height = ui->heightBox->value();
	return params;
}
