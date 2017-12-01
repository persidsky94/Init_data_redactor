#include <QVBoxLayout>
#include <QLabel>
#include "recievergroupeditor.h"

RecieverGroupEditor::RecieverGroupEditor(QWidget *parent) : QObject(parent)
{
	_widget = new QWidget(parent);
	_widget->setFixedWidth(300);
	_widget->setStyleSheet("border: 1px solid black");
	auto layout = new QVBoxLayout();
	_widget->setLayout(layout);
	auto label = new QLabel("Reciever group editor");
	_paramsInfo = new RecieverGroupInfo(_widget);
	_setButton = new QPushButton(QString("set"), _widget);
	layout->addWidget(label);
	layout->addWidget(_paramsInfo);
	layout->addWidget(_setButton);
	layout->addStretch();

	QObject::connect(this->_setButton, &QPushButton::clicked, this, &RecieverGroupEditor::on_setButton_clicked);
}

RecieverGroupEditor::~RecieverGroupEditor()
{

}

void RecieverGroupEditor::addSelfToLayout(QLayout *layout)
{
	if (_widget)
		layout->addWidget(_widget);
}

void RecieverGroupEditor::show()
{
	if (_widget)
		_widget->show();
}

void RecieverGroupEditor::hide()
{
	if (_widget)
		_widget->hide();
}

void RecieverGroupEditor::updateParams(recieverGroupParams params)
{
	if (_paramsInfo)
		_paramsInfo->updateParams(params);
}

void RecieverGroupEditor::initWithParams(recieverGroupParams params)
{
	updateParams(params);
}

void RecieverGroupEditor::on_setButton_clicked()
{
	if (_paramsInfo)
		emit setParams(_paramsInfo->constructParams());
}
