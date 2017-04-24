#include "sourceoptions.h"
#include "ui_sourceoptions.h"

SourceOptions::SourceOptions(QWidget *parent, QRectF sceneBR, source_params params) :
	QDialog(parent),
	ui(new Ui::SourceOptions)
{
	ui->setupUi(this);
	setBoxEnums();
	setMaxValues(sceneBR);
	setParams(params);
}

void SourceOptions::setBoxEnums()
{
	auto meta_object = this->metaObject();
	auto sourceEnumIndex = meta_object->indexOfEnumerator("SourceType");
	auto signalEnumIndex = meta_object->indexOfEnumerator("SignalType");
	auto source_enum = meta_object->enumerator(sourceEnumIndex);
	auto signal_enum = meta_object->enumerator(signalEnumIndex);
	for (int i=0; i<source_enum.keyCount();++i)
	{
		ui->sourceComboBox->addItem(source_enum.key(i), i);
	}
	for (int i=0; i<signal_enum.keyCount();++i)
	{
		ui->signalComboBox->addItem(signal_enum.key(i), i);
	}
}

void SourceOptions::setMaxValues(QRectF sceneBR)
{
	ui->sourcexBox->setMinimum(sceneBR.topLeft().rx());
	ui->sourcexBox->setMaximum(sceneBR.bottomRight().rx());
	ui->sourceyBox->setMinimum(sceneBR.topLeft().ry());
	ui->sourceyBox->setMaximum(sceneBR.bottomRight().ry());
}

void SourceOptions::setParams(source_params params)
{
	ui->sourceNameLine->setText(params.name);
	ui->sourceComboBox->setCurrentIndex(ui->sourceComboBox->findData(params.sourceType));
	ui->signalComboBox->setCurrentIndex(ui->signalComboBox->findData(params.signalType));
	ui->sourcexBox->setValue(params.x);
	ui->sourceyBox->setValue(params.y);
}

SourceOptions::source_params SourceOptions::getParams()
{
	return source_params(ui->sourceNameLine->text(),\
								SourceType(ui->sourceComboBox->currentData().toInt()),\
								SignalType(ui->signalComboBox->currentData().toInt()),\
								ui->sourcexBox->value(),\
								ui->sourceyBox->value());
}

SourceOptions::~SourceOptions()
{
	delete ui;
}
