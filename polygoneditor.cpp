#include "polygoneditor.h"
#include "ui_polygoneditor.h"

PolygonEditor::PolygonEditor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PolygonEditor)
{
	ui->setupUi(this);
}

PolygonEditor::~PolygonEditor()
{
	delete ui;
}

void PolygonEditor::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}

polygonParams PolygonEditor::constructParams()
{
	polygonParams params;
	params.name = this->ui->nameLine->text();
	params.density = this->ui->densityBox->value();
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void PolygonEditor::initWithParams(polygonParams params)
{
	updateParams(params);
}

void PolygonEditor::updateParams(polygonParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->densityBox->setValue(params.density);
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
