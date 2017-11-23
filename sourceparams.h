#ifndef SOURCEPARAMS_H
#define SOURCEPARAMS_H

#include <QString>

class sourceParams
{
	Q_OBJECT
	Q_ENUMS(SourceType)
	Q_ENUMS(SignalType)

public:
	enum SourceType {Point};
	enum SignalType {Sin, Cos};

	QString name;
	SourceType sourceType;
	SignalType signalType;
	int x;
	int y;
}

#endif // SOURCEPARAMS_H
