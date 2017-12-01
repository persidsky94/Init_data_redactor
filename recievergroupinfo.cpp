#include "recievergroupinfo.h"
#include "ui_recievergroupinfo.h"

RecieverGroupInfo::RecieverGroupInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RecieverGroupInfo)
{
	ui->setupUi(this);
}

RecieverGroupInfo::~RecieverGroupInfo()
{
	delete ui;
}

recieverGroupParams RecieverGroupInfo::constructParams()
{
	recieverGroupParams params;
	params.name = this->ui->nameLine->text();
	params.recieversNumber = this->ui->reciverNumberBox->value();
	params.y =  this->ui->yBox->value();
	params.firstx = this->ui->firstxBox->value();
	params.deltax = this->ui->deltaxBox->value();
	return params;
}

void RecieverGroupInfo::initWithParams(recieverGroupParams params)
{
	updateParams(params);
}

void RecieverGroupInfo::updateParams(recieverGroupParams params)
{
	this->ui->nameLine->setText(params.name);
	this->ui->reciverNumberBox->setValue(params.recieversNumber);
	this->ui->yBox->setValue(params.y);
	this->ui->firstxBox->setValue(params.firstx);
	this->ui->deltaxBox->setValue(params.deltax);
}
