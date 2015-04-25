#ifndef VECTORCHOICEWIDGET_H
#define VECTORCHOICEWIDGET_H

#include <QWidget>
#include "ui_vectorchoicewidget.h"

#include <glm.hpp>

class VectorChoiceWidget : public QWidget
{
	Q_OBJECT

public:
	VectorChoiceWidget(QWidget *parent = 0);
	~VectorChoiceWidget();

	glm::vec3 getVector() const 
	{
		return glm::vec3(ui.spinBoxX->value(), ui.spinBoxY->value(), ui.spinBoxZ->value());
	};

	void changeVector(const glm::vec3& vector) {
		ui.spinBoxX->setValue(vector.x);
		ui.spinBoxX->setValue(vector.y);
		ui.spinBoxX->setValue(vector.z);
	};

private:
	Ui::VectorChoiceWidget ui;

signals:
	void vectorChanged();
};

#endif // VECTORCHOICEWIDGET_H
