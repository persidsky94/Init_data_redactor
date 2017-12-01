#ifndef SOURCEITEM_H
#define SOURCEITEM_H

#include <QObject>
#include <QString>

#include <moveitem.h>
#include <sourceparams.h>

class SourceItem : public MoveItem
{
	Q_OBJECT
public:
	explicit SourceItem(sourceParams params, QObject *parent/* = 0*/);
	~SourceItem();
	sourceParams getParams();
	void setParams(sourceParams params);
	QString getName() {return getParams().name;}

signals:
	void paramsChanged(sourceParams& params);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QString getType();
	void on_positionIsSet();

	const static int _sourceSize = 12;
	sourceParams _params;
};

#endif // SOURCEITEM_H
