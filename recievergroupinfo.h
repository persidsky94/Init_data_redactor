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

signals: //to item
	void setParams(recieverGroupParams params);

private:
	Ui::RecieverGroupInfo *ui;

//slots from item
	void updateParams(recieverGroupParams params);
};

#endif // RECIEVERGROUPINFO_H
