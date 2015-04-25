#include "bezierSurface.h"

using namespace Shapes;
using namespace std;

BezierSurface::BezierSurface(vector<glm::vec3> controlPoints, int nbOfControlPointsInACurve,
	int numberOfColumn, int numberOfRow, glm::vec4 color)
	:controlPoints(controlPoints), nbOfControlPointsInACurve(nbOfControlPointsInACurve),
	numberOfColumn(numberOfColumn), numberOfRow(numberOfRow), color(color),
	Shapes::SceneObject("Bezier surface (" + to_string(controlPoints.size()) + " control points)", GL_TRIANGLE_STRIP)
{
	getTrianglePoints();
}

BezierSurface::~BezierSurface()
{
}

void BezierSurface::getTrianglePoints()
{
	//Calculer le nombre de points dans les courbes (horizontales et verticales)
	int nbOfPointsColumn = ((DEFAULT_NB_POINTS_IN_A_CURVE % numberOfColumn) == 0) ? 
						DEFAULT_NB_POINTS_IN_A_CURVE : findNumberOfPoints(numberOfColumn);

	int nbOfPointsRow = ((DEFAULT_NB_POINTS_IN_A_CURVE % numberOfRow) == 0) ?
							DEFAULT_NB_POINTS_IN_A_CURVE : findNumberOfPoints(numberOfRow);

	//Calculer des valeurs à incrémenter 
	int incrementPointsColumn = nbOfPointsColumn / numberOfColumn;
	int incrementPointsRow = nbOfPointsRow / numberOfRow;

	int columnCount = 0;

	constructInitialBezierCurves(nbOfPointsColumn);

	for (int i = 0; i <= numberOfColumn; i++)
	{
		vector<glm::vec3> tempList;
		for (int j = 0; j < initialBezierCurves.size(); j++)
		{
			glm::vec3* point = initialBezierCurves[j].getPointAt(columnCount);
			tempList.push_back(*point);
		}

		Bezier curve(tempList, nbOfPointsRow);
		for (int j = 0; j < curve.getCurvePoints().size(); j += incrementPointsRow)
		{
			pointList.push_back(*curve.getCurvePoints()[j]);
		}

		int indexLastPoint = curve.getCurvePoints().size() - 1;
		pointList.push_back(*curve.getCurvePoints()[indexLastPoint]); //Point 999 non atteint

		columnCount += incrementPointsColumn;
		columnCount = (columnCount == curve.getCurvePoints().size()) ? indexLastPoint : columnCount; //Atteindre point 999
	}
}

GLuint* BezierSurface::indices()
{
	int index = 0;
	GLuint* indices = new uint[getIndicesCount()];

	for (int i = 0; i < numberOfColumn; i++)
	{
		int firstIndice = (i * (numberOfRow + 1));
		int secondIndice = (firstIndice + (numberOfRow + 1));

		int indice1 = firstIndice;
		int indice2 = secondIndice;

		indices[index++] = indice1;
		indices[index++] = indice2;

		for (int j = 0; j < numberOfRow; j++)
		{
			indice1++;
			indice2++;

			indices[index++] = indice1;
			indices[index++] = indice2;
		}

		//Nécessaire pour pouvoir faire une autre colonne de triangles
		for (int j = 0; j < numberOfRow; j++)
		{
			indices[index++] = indice2;
			indice2--;
			indices[index++] = indice2;
		}
	}
	return indices;
}

GLfloat* BezierSurface::vertices()
{
	GLfloat* vertices = new float[this->pointList.size() * Utilities::Vertex::VERTEX_SIZE];

	int index = 0;

	for (int i = 0; i < pointList.size(); i++)
	{
		vertices[index++] = pointList[i].x;
		vertices[index++] = pointList[i].y;
		vertices[index++] = pointList[i].z;

		vertices[index++] = color[0];
		vertices[index++] = color[1];
		vertices[index++] = color[2];
		vertices[index++] = color[3];

		index++; index++;

		index++; index++; index++;
	}

	return vertices;
}

void BezierSurface::constructInitialBezierCurves(int nbOfPointsColumn)
{
	for (int i = 0; i < controlPoints.size(); i += nbOfControlPointsInACurve)
	{
		vector<glm::vec3>* temp = new vector<glm::vec3>();
		for (int j = 0; j < nbOfControlPointsInACurve; j++)
		{
			temp->push_back(controlPoints[i + j]);
		}

		Bezier tempCurve(*temp, nbOfPointsColumn);
		this->initialBezierCurves.push_back(tempCurve);
	}
}

int BezierSurface::findNumberOfPoints(int count)
{
	int numberOfPoints = count;
	bool isValid = false;

	//Vérifier que le nombre de point est supérieur à MIN_NB_POINTS 
	while (!isValid){
		numberOfPoints = (numberOfPoints * 10);
		if (numberOfPoints >= MIN_NB_POINTS) isValid = true;
	}
	return numberOfPoints;
}
