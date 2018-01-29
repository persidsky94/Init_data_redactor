#include <QVBoxLayout>
#include <QLabel>
#include "polygoneditor.h"

PolygonEditor::PolygonEditor(QWidget *parent) : QObject(parent)
{
	_widget = new QWidget(parent);
	_widget->setFixedWidth(300);
	_widget->setStyleSheet("border: 1px solid black");
	auto layout = new QVBoxLayout();
	auto label = new QLabel("Polygon editor");
	_polygonParamsInfo = new PolygonInfo(_widget);
	bool needDuplicateButton = true;
	_vertexListManager = new ItemListManager(_widget, needDuplicateButton);
	_vertexEditor = new VertexEditor(_widget);
	_setPolygonParamsButton = new QPushButton(QString("set"), _widget);

	layout->addWidget(label);
	layout->addWidget(_polygonParamsInfo);
	layout->addWidget(_setPolygonParamsButton);
	_vertexListManager->addSelfToLayout(layout);
	_vertexEditor->addSelfToLayout(layout);
	layout->addStretch();

	_widget->setLayout(layout);

//	bindVertexListManagerToSelf();
	QObject::connect(this->_setPolygonParamsButton, &QPushButton::clicked, this, &PolygonEditor::on_setButton_clicked);
}

PolygonEditor::~PolygonEditor()
{

}

void PolygonEditor::addSelfToLayout(QLayout *layout)
{
	if (_widget)
		layout->addWidget(_widget);
}

void PolygonEditor::show()
{
	if (_widget)
		_widget->show();
}

void PolygonEditor::hide()
{
	if (_widget)
		_widget->hide();
}

void PolygonEditor::updateParams(polygonParams params)
{
	if (_polygonParamsInfo)
		_polygonParamsInfo->updateParams(params);
}

void PolygonEditor::initWithParams(polygonParams params)
{
	updateParams(params);
}

void PolygonEditor::initVertexEditorWithParams(vertexParams params)
{
	_vertexEditor->initWithParams(params);
}

void PolygonEditor::on_setButton_clicked()
{
	if (_polygonParamsInfo)
		emit setParams(_polygonParamsInfo->constructParams());
}

void PolygonEditor::makeVertexListManagerCorrespondingToPolygonItem(PolygonItem *polygon)
{
//	clearVertexListManager();
	_vertexListManager->parsePolygon(polygon);
}

void PolygonEditor::clearVertexListManager()
{
	_vertexListManager->clearList();
}

void PolygonEditor::bindVertexListManagerToSelf()
{
	QObject::connect(_vertexListManager, &ItemListManager::selectContainerItem, this, &PolygonEditor::rebindVertexEditor);
}

void PolygonEditor::rebindVertexEditor(MoveItem *newRedactedVertex)
{
	unbindVertexEditorFromEverything();
	bindVertexEditorToVertex(dynamic_cast<VertexItem *>(newRedactedVertex));
}

void PolygonEditor::bindVertexListManagerToPolygon(PolygonItem *polygon)
{
	QObject::connect(polygon, &PolygonItem::childVertexCreated, _vertexListManager, &ItemListManager::on_itemAddedToContainer);
	QObject::connect(polygon, &PolygonItem::childVertexDeleted, _vertexListManager, &ItemListManager::on_itemDeletedFromContainer);
    QObject::connect(polygon, &PolygonItem::childVertexSelected, _vertexListManager, &ItemListManager::on_itemSelectedInContainer);
    _vertexListManager->addSignalSender(polygon);
	QObject::connect(_vertexListManager, &ItemListManager::duplicateContainerItem, polygon, &PolygonItem::on_duplicateVertex);
	QObject::connect(_vertexListManager, &ItemListManager::deleteContainerItem, polygon, &PolygonItem::on_deleteVertex);
    QObject::connect(_vertexListManager, &ItemListManager::selectContainerItem, polygon, &PolygonItem::on_childVertexSelected);
}

void PolygonEditor::unbindVertexListManagerFromEverything()
{
	QObject::disconnect(_vertexListManager, 0, 0, 0);
    _vertexListManager->unbindAllSignalSenders();
}

void PolygonEditor::bindVertexEditorToVertex(VertexItem *vertex)
{
	QObject::connect(vertex, &VertexItem::paramsChanged, _vertexEditor, &VertexEditor::initWithParams);
	QObject::connect(_vertexEditor, &VertexEditor::setParams, vertex, &VertexItem::setParams);
}

void PolygonEditor::unbindVertexEditorFromEverything()
{
	QObject::disconnect(_vertexEditor, 0, 0, 0);
}
