#ifndef SOURCEITEM_H
#define SOURCEITEM_H

#include <QObject>
#include <QString>

#include <moveitem.h>
#include <sourceoptions.h>

class SourceItem : public MoveItem
{
	Q_OBJECT
public:
	explicit SourceItem(QObject *parent = 0);
	~SourceItem();


private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();

	SourceOptions::SourceType type = SourceOptions::SourceType::Point;
	SourceOptions::SignalType signal = SourceOptions::SignalType::Sin;

private slots:
	void on_optionsButton_clicked();
};

#endif // SOURCEITEM_H
