#include "vertexinfo.h"
#include "ui_vertexeditor.h"

VertexInfo::VertexInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::VertexInfo)
{
	ui->setupUi(this);
}

VertexInfo::~VertexInfo()
{
	delete ui;
}

void VertexInfo::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}

vertexParams VertexInfo::constructParams()
{
	vertexParams params;
	params.name = this->ui->nameLine->text();
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void VertexInfo::initWithParams(vertexParams params)
{
	updateParams(params);
}

void VertexInfo::updateParams(vertexParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
