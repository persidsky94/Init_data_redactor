#ifndef SOURCEOPTIONS_H
#define SOURCEOPTIONS_H

#include <QDialog>

//#include <sourceitem.h>

namespace Ui {
class SourceOptions;
}

class SourceOptions : public QDialog
{
	Q_OBJECT
	Q_ENUMS(SourceType)
	Q_ENUMS(SignalType)

public:
	explicit SourceOptions(QWidget *parent = 0);
	~SourceOptions();

	enum SourceType {Point};
	enum SignalType {Sin, Cos};

private:
	Ui::SourceOptions *ui;
};

#endif // SOURCEOPTIONS_H
