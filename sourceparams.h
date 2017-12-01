#ifndef SOURCEPARAMS_H
#define SOURCEPARAMS_H

#include <QObject>
#include <QString>
#include <QMetaEnum>



struct sourceParams
{
	enum SignalType {Sin, Cos};

	QString name;
	SignalType signalType;
	int x;
	int y;
};

#endif // SOURCEPARAMS_H
