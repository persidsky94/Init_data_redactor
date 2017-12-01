#include "vertexeditor.h"
#include "ui_vertexeditor.h"

VertexEditor::VertexEditor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::VertexEditor)
{
	ui->setupUi(this);
}

VertexEditor::~VertexEditor()
{
	delete ui;
}

void VertexEditor::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}

vertexParams VertexEditor::constructParams()
{
	vertexParams params;
	params.name = this->ui->nameLine->text();
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void VertexEditor::initWithParams(vertexParams params)
{
	updateParams(params);
}

void VertexEditor::updateParams(vertexParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
