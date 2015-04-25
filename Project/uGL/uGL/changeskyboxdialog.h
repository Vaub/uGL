#ifndef CHANGESKYBOXDIALOG_H
#define CHANGESKYBOXDIALOG_H

#include <QDialog>
#include <QtGui\qopenglfunctions_3_3_core.h>
#include "ui_changeskyboxdialog.h"
#include "cubemap.h"

class ChangeSkyboxDialog : public QDialog
{
	Q_OBJECT

public:
	ChangeSkyboxDialog(QOpenGLFunctions_3_3_Core* ogl,QWidget *parent = 0);
	~ChangeSkyboxDialog();

	Textures::Cubemap* loadCubemap();

	bool isPictureLoaded() const;

private:
	Ui::ChangeSkyboxDialog ui;

	bool picturesLoaded = false;
	bool singlePicture;

	QOpenGLFunctions_3_3_Core* ogl;

	std::string singlePicturePath;
	std::string singleDownPath;
	std::string singleFrontPath;
	std::string singleBackPath;
	std::string singleRightPath;
	std::string singleLeftPath;
	//std::string multiplePicturePath;

	std::string loadSinglePath(const std::string& filters = "");
	
	//std::string loadDirectory(const std::string& filters = "");

	Textures::Cubemap* ChangeSkyboxDialog::importDocumentPicture();
	Textures::Cubemap* ChangeSkyboxDialog::importFilePicture();

private slots:
	void loadPicture();
	void loadTopPicture();
	void loadDownPicture();
	void loadFrontPicture();
	void loadBackPicture();
	void loadRightPicture();
	void loadLeftPicture();
	void cancel();
	void accept();
};

#endif // CHANGESKYBOXDIALOG_H
