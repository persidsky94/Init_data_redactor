#include <QVBoxLayout>
#include <QLabel>
#include "vertexeditor.h"

VertexEditor::VertexEditor(QWidget *parent) : QObject(parent)
{
	_widget = new QWidget(parent);
	_widget->setFixedWidth(300);
	_widget->setStyleSheet("border: 1px solid black");
	auto layout = new QVBoxLayout();
	_widget->setLayout(layout);
	auto label = new QLabel("Vertex editor");
	_paramsInfo = new VertexInfo(_widget);
	_setButton = new QPushButton(QString("set"), _widget);
	layout->addWidget(label);
	layout->addWidget(_paramsInfo);
	layout->addWidget(_setButton);
	layout->addStretch();

	QObject::connect(this->_setButton, &QPushButton::clicked, this, &VertexEditor::on_setButton_clicked);
}

VertexEditor::~VertexEditor()
{

}

void VertexEditor::addSelfToLayout(QLayout *layout)
{
	if (_widget)
		layout->addWidget(_widget);
}

void VertexEditor::show()
{
	if (_widget)
		_widget->show();
}

void VertexEditor::hide()
{
	if (_widget)
		_widget->hide();
}

void VertexEditor::updateParams(vertexParams params)
{
	if (_paramsInfo)
		_paramsInfo->updateParams(params);
}

void VertexEditor::initWithParams(vertexParams params)
{
	updateParams(params);
}

void VertexEditor::on_setButton_clicked()
{
	if (_paramsInfo)
		emit setParams(_paramsInfo->constructParams());
}
