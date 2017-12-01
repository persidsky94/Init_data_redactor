#ifndef RECIEVERGROUPINFO_H
#define RECIEVERGROUPINFO_H

#include <QWidget>

#include <recievergroupparams.h>

namespace Ui {
class RecieverGroupInfo;
}

class RecieverGroupInfo : public QWidget
{
	Q_OBJECT

public:
	explicit RecieverGroupInfo(QWidget *parent = 0);
	~RecieverGroupInfo();
	void initWithParams(recieverGroupParams params);
	recieverGroupParams constructParams();

	//for editor
	void updateParams(recieverGroupParams params);

signals: //to item
	void setParams(recieverGroupParams params);

private:
	Ui::RecieverGroupInfo *ui;

};

#endif // RECIEVERGROUPINFO_H
