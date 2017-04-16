#include "sourceoptions.h"
#include "ui_sourceoptions.h"

SourceOptions::SourceOptions(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SourceOptions)
{
	ui->setupUi(this);
}

SourceOptions::~SourceOptions()
{
	delete ui;
}
