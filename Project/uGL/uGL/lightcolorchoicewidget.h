#ifndef LIGHTCOLORCHOICEWIDGET_H
#define LIGHTCOLORCHOICEWIDGET_H

#include <QWidget>
#include "ui_lightcolorchoicewidget.h"

class LightcolorChoiceWidget : public QWidget
{
	Q_OBJECT

public:
	LightcolorChoiceWidget(QWidget *parent = 0);
	~LightcolorChoiceWidget();

private:
	Ui::LightcolorChoiceWidget ui;
};

#endif // LIGHTCOLORCHOICEWIDGET_H
