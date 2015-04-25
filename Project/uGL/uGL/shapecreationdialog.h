#ifndef SHAPECREATIONDIALOG_H
#define SHAPECREATIONDIALOG_H

#include <QDialog>
#include "ui_shapecreationdialog.h"

class ShapeCreationDialog : public QDialog
{
	Q_OBJECT

public:
	ShapeCreationDialog(QWidget *parent = 0);
	~ShapeCreationDialog();

private:
	Ui::ShapeCreationDialog ui;
};

#endif // SHAPECREATIONDIALOG_H
