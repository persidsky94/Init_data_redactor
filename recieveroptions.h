#ifndef RECIEVEROPTIONS_H
#define RECIEVEROPTIONS_H

#include <QDialog>

namespace Ui {
class recieveroptions;
}

class recieveroptions : public QDialog
{
	Q_OBJECT
	Q_ENUMS(RecieverType)

public:
	enum RecieverType {HorizontalLine};

	struct reciever_params
	{
		QString name;
		RecieverType recieverType;
		int recieversNumber;
		int y;
		int firstx;
		int lastx;
	};

	explicit recieveroptions(QWidget *parent = 0);
	~recieveroptions();

private:
	Ui::recieveroptions *ui;
};

#endif // RECIEVEROPTIONS_H
