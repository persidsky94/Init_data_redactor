#ifndef TOINITDATACONVERTER_H
#define TOINITDATACONVERTER_H

#include <QObject>

class ToInitDataConverter : public QObject
{
	Q_OBJECT
public:
	explicit ToInitDataConverter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TOINITDATACONVERTER_H