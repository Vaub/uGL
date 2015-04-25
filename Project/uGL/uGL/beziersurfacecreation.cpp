#include "beziersurfacecreation.h"

BezierSurfaceCreation::BezierSurfaceCreation(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.addBezierCurveButton, SIGNAL(clicked()), this, SLOT(addBezierCurve()));
	connect(ui.deleteBezierCurveButton, SIGNAL(clicked()), this, SLOT(deleteBezierCurve()));

	connect(ui.curveList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyBezierCurve(QListWidgetItem*)));

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	findNumberOfPointsInACurve();
}

BezierSurfaceCreation::~BezierSurfaceCreation()
{

}

void BezierSurfaceCreation::addBezierCurve()
{
	string newCurve = getOutputFromBezierCurveDialog("");
	if (!newCurve.empty())
	{
		pointList.push_back(newCurve);
		ui.curveList->addItem("Bezier curve points: \n   " + QString::fromStdString(formatStrPoint(newCurve)));
	}
}

void BezierSurfaceCreation::deleteBezierCurve()
{
	qDeleteAll(ui.curveList->selectedItems());
}

void BezierSurfaceCreation::modifyBezierCurve(QListWidgetItem* selectedCurve)
{
	int index = ui.curveList->selectionModel()->currentIndex().row(); //index de l'item sélectionné
	string points = pointList[index];

	string output = getOutputFromBezierCurveDialog(points);
	if (!output.empty())
	{
		selectedCurve->setText("Bezier curve points: \n   " + QString::fromStdString(formatStrPoint(output)));
		pointList[index] = output; 
	}
}

string BezierSurfaceCreation::formatStrPoint(const string strPoint)
{
	string returnString;
	vector<string> coordList = getStringCoord(strPoint);

	for (int i = 1; i <= coordList.size(); i += 3)
	{
		returnString += ("(" + coordList[i-1] + ", " + coordList[i] + ", " + coordList[i+1] + ")   ");
	}

	return returnString;
}

vector<glm::vec3>* BezierSurfaceCreation::getPointList()
{
	int count = ui.curveList->count();
	vector<glm::vec3>* points = new vector<glm::vec3>();

	for (int i = 0; i < count; i++)
	{
		string temp = pointList[i];
		vector<glm::vec3>* tempCurve = getPointsFromString(temp);
		points->insert(points->end(), tempCurve->begin(), tempCurve->end());
	}
	return points;
}

void BezierSurfaceCreation::findNumberOfPointsInACurve()
{
	this->numberOfControlPointsPerCurve = QInputDialog::getInt(NULL, "Number of control points",
		"Number of control points in a curve", 4, 2, 20);
	
	ui.numberOfPointsLabel->setText(QString::number(numberOfControlPointsPerCurve));
}

vector<glm::vec3>* BezierSurfaceCreation::getPointsFromString(const string strPoint)
{
	vector<string> coordList = getStringCoord(strPoint);
	vector<glm::vec3>* points = new vector<glm::vec3>();

	//Conversion en points
	for (int i = 1; i <= coordList.size(); i += 3)
	{
		glm::vec3 temp(stod(coordList[i - 1]), stod(coordList[i]), stod(coordList[i + 1]));
		points->push_back(temp);
	}
	return points;
}

//Obtenir les points de la boîte de dialogue BezierCurveCreation
string BezierSurfaceCreation::getOutputFromBezierCurveDialog(const string strPoints)
{
	string returnedString;
	BezierCurveCreation* curveDialog = new BezierCurveCreation();

	if (!strPoints.empty())
		curveDialog->initialiseWindow(strPoints);

	if (curveDialog->exec() == QDialog::Accepted)
	{
		if (curveDialog->getPointList().size() != numberOfControlPointsPerCurve)
		{
			QMessageBox::warning(NULL, "Error!", "Need " + QString::number(numberOfControlPointsPerCurve) + " control points!");
		}
		else
		{
			string curve = curveDialog->getStrPointList();	//Chercher les points du dialogue
			returnedString = curve;							
		}
	}
	curveDialog->close();
	return returnedString;
}

vector<string> BezierSurfaceCreation::getStringCoord(const string strPoint)
{
	int position = 0;
	string point = strPoint;
	string comma = ",";

	vector<string> coordList;;

	while ((position = point.find(comma)) != string::npos)
	{
		string temp = point.substr(0, position);
		coordList.push_back(temp);
		point.erase(0, position + comma.length());
	}

	return coordList;
}

int BezierSurfaceCreation::getNumberOfColumn()
{
	return ui.columnSpinBox->value();
}

int BezierSurfaceCreation::getNumberOfRow()
{
	return ui.rowSpinBox->value();
}

int BezierSurfaceCreation::getNumberOfControlPoints()
{
	return this->numberOfControlPointsPerCurve;
}

int BezierSurfaceCreation::getNumberOfCurve()
{
	return ui.curveList->count();
}
