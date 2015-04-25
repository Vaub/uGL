#include "importmodeldialog.h"

#include <qfiledialog.h>

ImportModelDialog::ImportModelDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);

	connect(ui.importModel, SIGNAL(clicked()), this, SLOT(loadModel()));
	connect(ui.importTexture, SIGNAL(clicked()), this, SLOT(loadTextures()));

	connect(ui.okAction, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.cancelAction, SIGNAL(clicked()), this, SLOT(cancel()));
}

ImportModelDialog::~ImportModelDialog()
{

}

std::string ImportModelDialog::loadPath(const std::string& filters)
{
	return QFileDialog::getOpenFileName(this, tr("Open file"), "", tr(filters.c_str())).toStdString();
}

void ImportModelDialog::loadModel()
{
	modelPath = loadPath();
	ui.modelPath->setText(modelPath.c_str());
}

void ImportModelDialog::loadTextures()
{
	texturePath = loadPath();
	ui.texturePath->setText(texturePath.c_str());
}


void ImportModelDialog::ok()
{
	modelLoaded = true;
	this->hide();
}

void ImportModelDialog::cancel()
{
	modelLoaded = false;
	this->hide();
}