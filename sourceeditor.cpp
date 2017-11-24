#include "sourceeditor.h"
#include "ui_sourceeditor.h"

SourceEditor::SourceEditor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SourceEditor)
{
	setBoxEnums();
	ui->setupUi(this);
}

void SourceEditor::setBoxEnums()
{
	auto meta_object = sourceParams::metaObject();
	auto signalEnumIndex = meta_object->indexOfEnumerator("SignalType");
	auto signal_enum = meta_object->enumerator(signalEnumIndex);
	for (int i=0; i<signal_enum.keyCount();++i)
	{
		ui->signalTypeComboBox->addItem(signal_enum.key(i), i);
	}
}

void SourceEditor::setMaxValues(QRectF sceneBR)
{
	ui->xBox->setMinimum(sceneBR.topLeft().rx());
	ui->xBox->setMaximum(sceneBR.bottomRight().rx());
	ui->yBox->setMinimum(sceneBR.topLeft().ry());
	ui->yBox->setMaximum(sceneBR.bottomRight().ry());
}


SourceEditor::~SourceEditor()
{
	delete ui;
}

sourceParams SourceEditor::constructParams()
{
	sourceParams params;
	params.name = this->ui->nameLine->text();
	params.signalType = sourceParams::SignalType(this->ui->signalTypeComboBox->currentData().toInt());
	params.y =  this->ui->yBox->value();
	params.x = this->ui->xBox->value();
	return params;
}

void SourceEditor::initWithParams(sourceParams params)
{
	updateParams(params);
}

void SourceEditor::updateParams(sourceParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->signalTypeComboBox->setCurrentIndex(ui->signalTypeComboBox->findData(params.signalType));
	this->ui->yBox->setValue(params.y);
	this->ui->xBox->setValue(params.x);
}
