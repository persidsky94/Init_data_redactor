#include "recieveroptions.h"
#include "ui_recieveroptions.h"

recieveroptions::recieveroptions(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::recieveroptions)
{
	ui->setupUi(this);
}

recieveroptions::~recieveroptions()
{
	delete ui;
}
