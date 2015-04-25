#ifndef COLORCHOICEWIDGET_H
#define COLORCHOICEWIDGET_H

#include <QWidget>
#include "ui_colorchoicewidget.h"

#include <glm.hpp>

class ColorChoiceWidget : public QWidget
{
	Q_OBJECT

public:
	ColorChoiceWidget(QWidget *parent = 0);
	~ColorChoiceWidget();

	glm::vec4 getCurrentColorF() const { return glm::vec4(currentColor.redF(), currentColor.greenF(), currentColor.blueF(), currentColor.alphaF()); }

	void changeColor(int r, int g, int b, int a = 255);
	void changeColor(const glm::vec4& color);

private:
	QColor currentColor;

	Ui::ColorChoiceWidget ui;
	void updateUiColor();

signals:
	void colorChanged(const QColor&);

private slots:
	void changeColor();
};

#endif // COLORCHOICEWIDGET_H
