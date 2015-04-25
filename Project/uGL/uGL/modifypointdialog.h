#ifndef MODIFYPOINTDIALOG_H
#define MODIFYPOINTDIALOG_H

#include <QDialog>
#include <glm.hpp>

#include "ui_modifypointdialog.h"

class ModifyPointDialog : public QDialog
{
	Q_OBJECT

public:
	ModifyPointDialog(QWidget *parent = 0);
	~ModifyPointDialog();

	glm::vec3* getPoint();

	void initialiseWindow(glm::vec3*);
	
private:
	Ui::ModifyPointDialog ui;
};

#endif // MODIFYPOINTDIALOG_H
