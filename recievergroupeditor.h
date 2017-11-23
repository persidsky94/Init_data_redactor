#ifndef RECIEVERGROUPEDITOR_H
#define RECIEVERGROUPEDITOR_H

#include <QWidget>

#include <recievergroupparams.h>

namespace Ui {
class RecieverGroupEditor;
}

class RecieverGroupEditor : public QWidget
{
	Q_OBJECT

public:
	explicit RecieverGroupEditor(QWidget *parent = 0);
	~RecieverGroupEditor();
	void initWithParams(recieverGroupParams params);
	recieverGroupParams constructParams();

signals: //to item
	void setParams(recieverGroupParams params);

private:
	Ui::RecieverGroupEditor *ui;

//slots from item
	void updateParams(recieverGroupParams params);
};

#endif // RECIEVERGROUPEDITOR_H
