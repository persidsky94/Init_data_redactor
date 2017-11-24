#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include <QWidget>

#include <sourceparams.h>

namespace Ui {
class SourceEditor;
}

class SourceEditor : public QWidget
{
	Q_OBJECT

public:
	explicit SourceEditor(QWidget *parent = 0);
	~SourceEditor();
	void initWithParams(sourceParams params);
	sourceParams constructParams();

signals: //to item
	void setParams(sourceParams params);

private:
	Ui::SourceEditor *ui;

	void setBoxEnums();
	void setMaxValues(QRectF sceneBR);
//slots from item
	void updateParams(sourceParams params);
};

#endif // SOURCEEDITOR_H
