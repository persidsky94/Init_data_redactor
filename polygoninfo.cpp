#include "polygoninfo.h"
#include "ui_polygoninfo.h"

PolygonInfo::PolygonInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PolygonInfo)
{
	ui->setupUi(this);
}

PolygonInfo::~PolygonInfo()
{
	delete ui;
}

void PolygonInfo::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}

polygonParams PolygonInfo::constructParams()
{
	polygonParams params;
	params.name = this->ui->nameLine->text();
	params.density = this->ui->densityBox->value();
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void PolygonInfo::initWithParams(polygonParams params)
{
	updateParams(params);
}

void PolygonInfo::updateParams(polygonParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->densityBox->setValue(params.density);
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
