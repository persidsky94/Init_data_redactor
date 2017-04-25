#ifndef SOURCEOPTIONS_H
#define SOURCEOPTIONS_H

#include <QDialog>
#include <QMetaEnum>


namespace Ui {
class SourceOptions;
}

class SourceOptions : public QDialog
{
	Q_OBJECT
	Q_ENUMS(SourceType)
	Q_ENUMS(SignalType)

public:
	enum SourceType {Point};
	enum SignalType {Sin, Cos};

	struct source_params
	{
		QString name;
		SourceType sourceType;
		SignalType signalType;
		int x;
		int y;

		source_params(QString _name = QString("src"), SourceType _sourceType = SourceType::Point,\
			SignalType _signalType = SignalType::Sin, int _x = 0, int _y = 0):
			name(_name), sourceType(_sourceType), signalType(_signalType), x(_x), y(_y){}

	};

	explicit SourceOptions(QWidget *parent, QRectF sceneBR, source_params params);
	~SourceOptions();
	source_params getParams();

private:
	void setBoxEnums();
	void setMaxValues(QRectF sceneBR);
	void setParams(source_params params);
	Ui::SourceOptions *ui;
};

#endif // SOURCEOPTIONS_H
