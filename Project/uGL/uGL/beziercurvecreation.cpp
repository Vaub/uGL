#include "beziercurvecreation.h"

BezierCurveCreation::BezierCurveCreation(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));
	connect(ui.deletePointButton, SIGNAL(clicked()), this, SLOT(erasePoint()));

	connect(ui.pointList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(modifyPoint(QListWidgetItem*)));

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

BezierCurveCreation::~BezierCurveCreation()
{

}

void BezierCurveCreation::addPoint()
{
	double x = ui.xSpinBox->value();
	double y = ui.ySpinBox->value();
	double z = ui.zSpinBox->value();
	
	ui.pointList->addItem(QString::number(x) + ", \t" + QString::number(y) + ", \t" + QString::number(z));
}

void BezierCurveCreation::erasePoint()
{
	qDeleteAll(ui.pointList->selectedItems());
}

void BezierCurveCreation::modifyPoint(QListWidgetItem* selectedPoint)
{
	glm::vec3* point = splitByComma(selectedPoint->text().toStdString());

	ModifyPointDialog* modifyPointDialog = new ModifyPointDialog();
	modifyPointDialog->initialiseWindow(point);						

	if (modifyPointDialog->exec() == QDialog::Accepted)
	{
		glm::vec3* modifiedPoint = modifyPointDialog->getPoint();		
		selectedPoint->setText(QString::number(modifiedPoint->x) + ", \t" + 
							QString::number(modifiedPoint->y) + ", \t" + 
							QString::number(modifiedPoint->z));
	}
	modifyPointDialog->close();
}

vector<glm::vec3> BezierCurveCreation::getPointList()
{
	vector<glm::vec3> points;

	for (int i = 0; i < ui.pointList->count(); i++)
	{
		QListWidgetItem* item = ui.pointList->item(i);
		glm::vec3* point = splitByComma(item->text().toStdString());
		points.push_back(*point);
	}
	return points;
}

string BezierCurveCreation::getStrPointList()
{
	string points;
	for (int i = 0; i < ui.pointList->count(); i++)
	{
		QListWidgetItem* item = ui.pointList->item(i);
		string stringToAdd = item->text().toStdString();

		stringToAdd.erase(remove(stringToAdd.begin(), stringToAdd.end(), '\t'), stringToAdd.end());	//Remove '\t'
		points += (stringToAdd + ",");
	}
	return points;
}

int BezierCurveCreation::getLineWidth()
{
	return ui.lineWidthSpinBox->value();
}

glm::vec3* BezierCurveCreation::splitByComma(const string stringPoint)
{
	glm::vec3* point = new glm::vec3();
	vector<double> coordinates;

	int nbPoint = 0;
	string comma = ",";
	string temp = stringPoint;

	while (nbPoint != 3)
	{
		int position = temp.find(comma);
		string coordinate = temp.substr(0, position);

		coordinates.push_back(stod(coordinate));
		temp.erase(0, position + comma.length());

		nbPoint++;
	}

	point->x = coordinates[0];
	point->y = coordinates[1];
	point->z = coordinates[2];

	return point;
}

void BezierCurveCreation::initialiseWindow(const string strPoints)
{
	string comma = ",";
	string points = strPoints;

	int position = 0;
	int index = 1;

	vector<string> coordList;

	while ((position = points.find(comma)) != string::npos)
	{
		string temp = points.substr(0, position);
		coordList.push_back(temp);
		points.erase(0, position + comma.length());

		if ((index % 3) == 0)
		{
			ui.pointList->addItem(QString::fromStdString(coordList[0]) +
						",\t" + QString::fromStdString(coordList[1]) + 
						",\t" + QString::fromStdString(coordList[2]));
			coordList.clear();
		}
		index++;
	}
}
