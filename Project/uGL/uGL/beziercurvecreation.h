#ifndef BEZIERCURVECREATION_H
#define BEZIERCURVECREATION_H

#include <QDialog>
#include <glm.hpp>
#include <string>
#include <algorithm>

#include "modifypointdialog.h"
#include "ui_beziercurvecreation.h"

using namespace std;

class BezierCurveCreation : public QDialog
{
	Q_OBJECT

public:
	BezierCurveCreation(QWidget *parent = 0);
	~BezierCurveCreation();

public slots:
	void addPoint();
	void erasePoint();
	void modifyPoint(QListWidgetItem*);

	vector<glm::vec3> getPointList();
	string getStrPointList();
	int getLineWidth();

	void initialiseWindow(const string strPoints);

private:
	Ui::BezierCurveCreation ui;

	glm::vec3* splitByComma(const string stringPoint);
};

#endif // BEZIERCURVECREATION_H
