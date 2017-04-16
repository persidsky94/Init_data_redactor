#ifndef SOURCEOPTIONS_H
#define SOURCEOPTIONS_H

#include <QDialog>

namespace Ui {
class SourceOptions;
}

class SourceOptions : public QDialog
{
	Q_OBJECT

public:
	explicit SourceOptions(QWidget *parent = 0);
	~SourceOptions();

private:
	Ui::SourceOptions *ui;
};

#endif // SOURCEOPTIONS_H
