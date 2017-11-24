#ifndef SOURCEPARAMS_H
#define SOURCEPARAMS_H

#include <QObject>
#include <QString>
#include <QMetaEnum>

class sourceParams
{
	Q_OBJECT
	Q_ENUMS(SignalType)

public:
	enum SignalType {Sin, Cos};

	QString name;
	SignalType signalType;
	int x;
	int y;
}

#endif // SOURCEPARAMS_H
