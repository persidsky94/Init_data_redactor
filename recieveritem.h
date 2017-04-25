#ifndef RECIEVERITEM_H
#define RECIEVERITEM_H

#include <QObject>
#include <QString>

#include <moveitem.h>

class RecieverItem : public MoveItem
{
	Q_OBJECT
public:
	explicit RecieverItem(QObject *parent = 0);
	~RecieverItem();

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
};

#endif // RECIEVERITEM_H
