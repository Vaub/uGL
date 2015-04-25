#ifndef BEZIERSURFACECREATION_H
#define BEZIERSURFACECREATION_H

#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <glm.hpp>
#include <string>
#include <algorithm>
#include "ui_beziersurfacecreation.h"
#include "beziercurvecreation.h"

using namespace std;

class BezierSurfaceCreation : public QDialog
{
	Q_OBJECT

public:
	BezierSurfaceCreation(QWidget *parent = 0);
	~BezierSurfaceCreation();

	int getNumberOfColumn();
	int getNumberOfRow();
	int getNumberOfControlPoints();
	int getNumberOfCurve();
	vector<glm::vec3>* getPointList();

public slots:
	void addBezierCurve();
	void deleteBezierCurve();
	void modifyBezierCurve(QListWidgetItem*);

private:
	Ui::BezierSurfaceCreation ui;

	int numberOfControlPointsPerCurve = 4;
	vector<string> pointList;

	void findNumberOfPointsInACurve();
	string formatStrPoint(const string);
	string getOutputFromBezierCurveDialog(const string);
	vector<glm::vec3>* getPointsFromString(const string);
	vector<string> getStringCoord(const string);
};

#endif // BEZIERSURFACECREATION_H
