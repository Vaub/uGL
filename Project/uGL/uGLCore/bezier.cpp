#include "bezier.h"

using namespace Shapes;
using namespace std;

Bezier::Bezier(vector<glm::vec3> controlPoints, int nbOfPointsInACurve, glm::vec4 color)
:controlPoints(controlPoints), nbOfPointsInACurve(nbOfPointsInACurve), color(color),
Shapes::SceneObject("Bezier curve (" + to_string(controlPoints.size()) + " control points)", GL_LINE_STRIP)
{
	findCurvePoints();
}

Bezier::~Bezier()
{
}

void Bezier::findCurvePoints()
{
	double t = 0;
	int degree = controlPoints.size() - 1;
	double incrementValue = 1.0f / nbOfPointsInACurve;

	while (t <= 1 && (this->curvePoints.size() < nbOfPointsInACurve))
	{
		glm::vec3* temp = getBezierPoint(degree, 0, t);
		this->curvePoints.push_back(temp);
		t += incrementValue;
	}
}

glm::vec3* Bezier::getBezierPoint(int degree, int index, double paramT)
{
	//Condition d'arrêt
	if (degree == 0)
		return &controlPoints[index];

	glm::vec3* p0 = getBezierPoint(degree - 1, index, paramT);			//Trouver Pi
	glm::vec3* p1 = getBezierPoint(degree - 1, index + 1, paramT);		//Trouver P(i+1)

	//Trouver b(t) = (1-t)Pi + t*P(i+1) pour les plans x,y,z
	double xCoord = calculateLinearInterpolation(p0->x, p1->x, paramT);
	double yCoord = calculateLinearInterpolation(p0->y, p1->y, paramT);
	double zCoord = calculateLinearInterpolation(p0->z, p1->z, paramT);

	glm::vec3* newPoint = new glm::vec3((float)xCoord, (float)yCoord, (float)zCoord);

	return newPoint;
}

double Bezier::calculateLinearInterpolation(float coord0, float coord1, double paramT)
{
	//B(t) = (1-t)B0(t) + t*B1(t)
	double result = ((1 - paramT)*coord0) + paramT*coord1;
	return result;
}

GLfloat* Bezier::vertices()
{
	GLfloat* vertices = new GLfloat[curvePoints.size() * Utilities::Vertex::VERTEX_SIZE];

	int index = 0;
	for (int i = 0; i < curvePoints.size(); i++)
	{
		vertices[index++] = curvePoints[i]->x;
		vertices[index++] = curvePoints[i]->y;
		vertices[index++] = curvePoints[i]->z;
		
		vertices[index++] = color[0];
		vertices[index++] = color[1];
		vertices[index++] = color[2];
		vertices[index++] = color[3];

		index++; index++;

		index++; index++; index++;
	}
	return vertices;
}

GLuint* Bezier::indices()
{
	GLuint* indices = new uint[getIndicesCount()];

	for (int i = 0; i < getIndicesCount(); i++)
	{
		indices[i] = i;
	}

	return indices;
}

void Bezier::modifyLineWidth(int width)
{
	this->lineWidth = width;
}

glm::vec3* Bezier::getPointAt(float index) const
{
	glm::vec3* temp = curvePoints[index];
	return temp;
}

vector<glm::vec3*> Bezier::getCurvePoints()
{
	return this->curvePoints;
}

void Bezier::render(
		int byteOffset,
		OpenGLContext* context,
		GLuint shaderProgramId,
		Camera::GenericCamera* camera)
{
	context->glLineWidth(lineWidth);
	SceneObject::render(byteOffset, context, shaderProgramId, camera);
	context->glLineWidth(DEFAULT_WIDTH);
}