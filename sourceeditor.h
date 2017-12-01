#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

#include <sourceinfo.h>

class SourceEditor : public QObject
{
	Q_OBJECT
	
public:
	explicit SourceEditor(QWidget *parent = nullptr);
	~SourceEditor();
	void addSelfToLayout(QLayout *layout);
	void initWithParams(sourceParams params);
	void show();
	void hide();
	
signals:
	void setParams(sourceParams params);
	
private:
	QWidget *_widget;
	SourceInfo *_paramsInfo;
	QPushButton *_setButton;
	
//slots from item
	void updateParams(sourceParams params);
//slots from ui
	void on_setButton_clicked();
};

#endif // SOURCEEDITOR_H
