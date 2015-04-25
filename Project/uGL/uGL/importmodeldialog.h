#ifndef IMPORTMODELDIALOG_H
#define IMPORTMODELDIALOG_H

#include <QDialog>
#include "ui_importmodeldialog.h"

class ImportModelDialog : public QDialog
{
	Q_OBJECT

public:
	ImportModelDialog(QWidget *parent = 0);
	~ImportModelDialog();

	const std::string& getModelPath() const { return modelPath; };
	const std::string& getTexturePath() const { return texturePath; };

	bool isModelLoaded() const { return modelLoaded; }

private:
	Ui::ImportModelDialog ui;

	bool modelLoaded = false;

	std::string modelPath;
	std::string texturePath;

	std::string loadPath(const std::string& filters = "");

private slots:
	void loadModel();
	void loadTextures();

	void ok();
	void cancel();
	
};

#endif // IMPORTMODELDIALOG_H
