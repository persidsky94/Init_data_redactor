#include "recievergroupeditor.h"
#include "ui_recievergroupeditor.h"

RecieverGroupEditor::RecieverGroupEditor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RecieverGroupEditor)
{
	ui->setupUi(this);
}

RecieverGroupEditor::~RecieverGroupEditor()
{
	delete ui;
}

recieverGroupParams RecieverGroupEditor::constructParams()
{
	recieverGroupParams params;
	params.name = this->ui->nameLine->text();
	params.recieversNumber = this->ui->reciverNumberBox->value();
	params.y =  this->ui->yBox->value();
	params.firstx = this->ui->firstxBox->value();
	params.deltax = this->ui->deltaxBox->value();
	return params;
}

void RecieverGroupEditor::initWithParams(recieverGroupParams params)
{
	updateParams(params);
}

void RecieverGroupEditor::updateParams(recieverGroupParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->reciverNumberBox->setValue(params.recieversNumber);
	this->ui->yBox->setValue(params.y);
	this->ui->firstxBox->setValue(params.firstx);
	this->ui->deltaxBox->setValue(params.deltax);
}
