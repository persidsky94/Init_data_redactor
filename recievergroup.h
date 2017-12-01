#ifndef RECIEVERGROUP_H
#define RECIEVERGROUP_H

#include <QObject>
#include <QString>

#include <recievergroupparams.h>
#include <moveitem.h>

class RecieverGroup: public MoveItem
{
	Q_OBJECT
public:
	explicit RecieverGroup(recieverGroupParams params, QObject *parent);
	~RecieverGroup();
	recieverGroupParams getParams() const;
	void setParams(recieverGroupParams params);
	QString getName() {return getParams().name;}

signals:
	void paramsChanged(recieverGroupParams params);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void drawSingleReciever(QPainter *painter, float x);
	QString getType();
	void on_positionIsSet();

	const static int _singleRecieverThickness = 12;
	recieverGroupParams _params;
};

#endif // RECIEVERGROUP_H
