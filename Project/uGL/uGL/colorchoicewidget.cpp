#include "colorchoicewidget.h"

#include <qcolordialog.h>

ColorChoiceWidget::ColorChoiceWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	currentColor = QColor(255, 255, 255);
	connect(ui.colorChoice, SIGNAL(clicked()), this, SLOT(changeColor()));

	updateUiColor();
}

ColorChoiceWidget::~ColorChoiceWidget()
{
	
}

void ColorChoiceWidget::changeColor(int r, int g, int b, int a) {
	currentColor = QColor(r, g, b, a);
	updateUiColor();
}

void ColorChoiceWidget::changeColor(const glm::vec4& color) {
	currentColor = QColor(255 * color.r, 255 * color.g, 255 * color.b, 255 * color.a);
}

void ColorChoiceWidget::changeColor() {
	currentColor = QColorDialog::getColor(currentColor, 0, "Choose a new color");
	updateUiColor();

	emit(colorChanged(currentColor));
}

void ColorChoiceWidget::updateUiColor() {

	std::string color = std::to_string(currentColor.red()) + ", " + std::to_string(currentColor.green()) + ", " +
		std::to_string(currentColor.blue()) + ((currentColor.alpha() < 255) ? ", " + std::to_string(currentColor.alpha()) : "");

	std::string colorStylesheet = "QPushButton { color:rgba(" + color + "); background-color:#aaa; font-weight:bold; } ";

	ui.colorChoice->setStyleSheet(colorStylesheet.c_str());
	ui.colorChoice->setText(color.c_str());
}




