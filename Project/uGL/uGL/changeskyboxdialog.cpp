#include "changeskyboxdialog.h"

#include <qfiledialog.h>

ChangeSkyboxDialog::ChangeSkyboxDialog(QOpenGLFunctions_3_3_Core* ogl, QWidget *parent)
	:ogl(ogl), QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);

	//connect(ui.importMultipleButton, SIGNAL(clicked()), this, SLOT(loadDocument()));
	connect(ui.importSingleButton, SIGNAL(clicked()), this, SLOT(loadPicture()));

	connect(ui.importTopButton, SIGNAL(clicked()), this, SLOT(loadTopPicture()));
	connect(ui.importDownButton, SIGNAL(clicked()), this, SLOT(loadDownPicture()));
	connect(ui.importFrontButton, SIGNAL(clicked()), this, SLOT(loadFrontPicture()));
	connect(ui.importBackButton, SIGNAL(clicked()), this, SLOT(loadBackPicture()));
	connect(ui.importLeftButton, SIGNAL(clicked()), this, SLOT(loadLeftPicture()));
	connect(ui.importRightButton, SIGNAL(clicked()), this, SLOT(loadRightPicture()));

	connect(ui.modifyButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

}

ChangeSkyboxDialog::~ChangeSkyboxDialog()
{

}


std::string ChangeSkyboxDialog::loadSinglePath(const std::string& filters)
{
	return QFileDialog::getOpenFileName(this, tr("Open file"), "", tr(filters.c_str())).toStdString();
}

/*std::string ChangeSkyboxDialog::loadDirectory(const std::string& filters)
{
	return QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()).toStdString();
}*/


void ChangeSkyboxDialog::loadPicture()
{
	singlePicturePath = loadSinglePath();
	ui.picturePathText->setText(singlePicturePath.c_str());
}
void ChangeSkyboxDialog::loadTopPicture()
{
	singlePicturePath = loadSinglePath();
	ui.textTop->setText(singlePicturePath.c_str());
}
void ChangeSkyboxDialog::loadDownPicture()
{
	singleDownPath = loadSinglePath();
	ui.textBottom->setText(singleDownPath.c_str());
}
void ChangeSkyboxDialog::loadFrontPicture()
{
	singleFrontPath = loadSinglePath();
	ui.textFront->setText(singleFrontPath.c_str());
}
void ChangeSkyboxDialog::loadBackPicture()
{
	singleBackPath = loadSinglePath();
	ui.textBack->setText(singleBackPath.c_str());
}
void ChangeSkyboxDialog::loadLeftPicture()
{
	singleLeftPath = loadSinglePath();
	ui.textLeft->setText(singleLeftPath.c_str());
}
void ChangeSkyboxDialog::loadRightPicture()
{
	singleRightPath = loadSinglePath();
	ui.textRight->setText(singleRightPath.c_str());
}



 Textures::Cubemap* ChangeSkyboxDialog::importFilePicture()
 {
	 Textures::Cubemap* cubemap = new Textures::Cubemap(ogl);
	 for (int i = 0; i < 6; i++)
	 {
		 cubemap->importImageAsTexture(singlePicturePath);
	 }
	 return cubemap;
 }

 Textures::Cubemap* ChangeSkyboxDialog::importDocumentPicture()
{
	Textures::Cubemap* cubemap = new Textures::Cubemap(ogl);

	cubemap->importImageAsTexture(singleRightPath);
	cubemap->importImageAsTexture(singleLeftPath);
	cubemap->importImageAsTexture(singleDownPath);
	cubemap->importImageAsTexture(singlePicturePath);
	cubemap->importImageAsTexture(singleBackPath);
	cubemap->importImageAsTexture(singleFrontPath);

	return cubemap;
}

void ChangeSkyboxDialog::accept()
{
	picturesLoaded = true;
	this->hide();
}

void ChangeSkyboxDialog::cancel()
{
	picturesLoaded = false;
	this->hide();
}
bool ChangeSkyboxDialog::isPictureLoaded() const
{
	return picturesLoaded;
}

Textures::Cubemap* ChangeSkyboxDialog::loadCubemap()
{
	if (!picturesLoaded)
	{
		throw std::runtime_error("Picture are not loaded!");
	}
	if (ui.comboBox->currentIndex() == 0)
		return importFilePicture();
	else
		return importDocumentPicture();

}