#ifndef RECIEVERGROUPEDITOR_H
#define RECIEVERGROUPEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QObject>

#include <recievergroupinfo.h>

class RecieverGroupEditor : public QObject
{
	Q_OBJECT

public:
	explicit RecieverGroupEditor(QWidget *parent = nullptr);
	~RecieverGroupEditor();

	void addSelfToLayout(QLayout *layout);
	void initWithParams(recieverGroupParams params);
	void show();
	void hide();

signals:
	void setParams(recieverGroupParams params);

private:
	QWidget *_widget;
	RecieverGroupInfo *_paramsInfo;
	QPushButton *_setButton;

//slots from item
	void updateParams(recieverGroupParams params);
//slots from ui
	void on_setButton_clicked();

};

#endif // RECIEVERGROUPEDITOR_H
