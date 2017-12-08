#ifndef VERTEXEDITOR_H
#define VERTEXEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

#include <vertexinfo.h>

class VertexEditor : public QObject
{
	Q_OBJECT

public:
	explicit VertexEditor(QWidget *parent = nullptr);
	~VertexEditor();
	void addSelfToLayout(QLayout *layout);
	void initWithParams(vertexParams params);
	void show();
	void hide();

signals:
	void setParams(vertexParams params);

private:
	QWidget *_widget;
	VertexInfo *_paramsInfo;
	QPushButton *_setButton;

//slots from item
	void updateParams(vertexParams params);
//slots from ui
	void on_setButton_clicked();
};

#endif // VERTEXEDITOR_H
