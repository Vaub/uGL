#include "modifypointdialog.h"

ModifyPointDialog::ModifyPointDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

ModifyPointDialog::~ModifyPointDialog()
{

}

glm::vec3* ModifyPointDialog::getPoint()
{
	double x = ui.xSpinBox->value();
	double y = ui.ySpinBox->value();
	double z = ui.zSpinBox->value();

	glm::vec3* point = new glm::vec3();
	point->x = x;
	point->y = y;
	point->z = z;

	return point;
}

void ModifyPointDialog::initialiseWindow(glm::vec3* currentPoint)
{
	ui.xSpinBox->setValue(currentPoint->x);
	ui.ySpinBox->setValue(currentPoint->y);
	ui.zSpinBox->setValue(currentPoint->z);
}
