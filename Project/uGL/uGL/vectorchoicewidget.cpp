#include "vectorchoicewidget.h"

VectorChoiceWidget::VectorChoiceWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.spinBoxX, SIGNAL(valueChanged(double)), this, SIGNAL(vectorChanged()));
	connect(ui.spinBoxY, SIGNAL(valueChanged(double)), this, SIGNAL(vectorChanged()));
	connect(ui.spinBoxZ, SIGNAL(valueChanged(double)), this, SIGNAL(vectorChanged()));
}

VectorChoiceWidget::~VectorChoiceWidget()
{

}
