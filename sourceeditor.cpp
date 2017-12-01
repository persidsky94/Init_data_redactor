#include <QVBoxLayout>
#include <QLabel>
#include "sourceeditor.h"

SourceEditor::SourceEditor(QWidget *parent) : QObject(parent)
{
	_widget = new QWidget(parent);
	_widget->setFixedWidth(300);
	_widget->setStyleSheet("border: 1px solid black");
	auto layout = new QVBoxLayout();
	_widget->setLayout(layout);
	auto label = new QLabel("Source editor");
	_paramsInfo = new SourceInfo(_widget);
	_setButton = new QPushButton(QString("set"), _widget);
//	auto vSpacer = new QSpacerItem;
//	vSpacer->set
	layout->addWidget(label);
	layout->addWidget(_paramsInfo);
	layout->addWidget(_setButton);
	layout->addStretch();

	QObject::connect(this->_setButton, &QPushButton::clicked, this, &SourceEditor::on_setButton_clicked);
}

SourceEditor::~SourceEditor()
{

}

void SourceEditor::addSelfToLayout(QLayout *layout)
{
	if (_widget)
		layout->addWidget(_widget);
}

void SourceEditor::show()
{
	if (_widget)
		_widget->show();
}

void SourceEditor::hide()
{
	if (_widget)
		_widget->hide();
}

void SourceEditor::updateParams(sourceParams params)
{
	if (_paramsInfo)
		_paramsInfo->updateParams(params);
}

void SourceEditor::initWithParams(sourceParams params)
{
	updateParams(params);
}

void SourceEditor::on_setButton_clicked()
{
	if (_paramsInfo)
		emit setParams(_paramsInfo->constructParams());
}
