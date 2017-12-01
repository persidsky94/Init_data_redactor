#include "sourceinfo.h"
#include "ui_sourceinfo.h"

SourceInfo::SourceInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SourceInfo)
{
	ui->setupUi(this);
	setBoxEnums();
	ui->signalTypeComboBox->setCurrentIndex(sourceParams::Sin);
}

void SourceInfo::setBoxEnums()
{
	ui->signalTypeComboBox->addItem(QString("Sin"), sourceParams::Sin);
	ui->signalTypeComboBox->addItem(QString("Cos"), sourceParams::Cos);
}

void SourceInfo::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}


SourceInfo::~SourceInfo()
{
	delete ui;
}

sourceParams SourceInfo::constructParams()
{
	sourceParams params;
	params.name = this->ui->nameLine->text();
	params.signalType = sourceParams::SignalType(this->ui->signalTypeComboBox->currentIndex());
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void SourceInfo::initWithParams(sourceParams params)
{
	updateParams(params);
}

void SourceInfo::updateParams(sourceParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->signalTypeComboBox->setCurrentIndex(ui->signalTypeComboBox->findData(params.signalType));
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
