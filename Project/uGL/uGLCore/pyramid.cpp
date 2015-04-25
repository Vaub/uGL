#include "pyramid.h"

using namespace Shapes;

Pyramid::Pyramid(uint base, float radius, float height)
	: base(Polygon(base, radius, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.0f)),
	summitVertex(Position(0.0f, 0.0f, height), Color(1.0f, 1.0f, 1.0f, 1.0f), TextureCoordinates(0.5f,0.5f), Normal(0,0,1)),
	Shapes::SceneObject(std::to_string(base) + "-sided base pyramid")
{
}


Pyramid::~Pyramid()
{
}

GLfloat* Pyramid::vertices()
{
	GLfloat* vertices = new float[(getVerticesCount() + 1) * Utilities::Vertex::VERTEX_SIZE];
	GLfloat* baseVertices = base.vertices();

	int i = 0;
	for (int index = 0; index < base.getVerticesCount() * Utilities::Vertex::VERTEX_SIZE; index++)
		vertices[i++] = baseVertices[index];

	for (int v = 0; v < Utilities::Vertex::VERTEX_SIZE; v++)
		vertices[i++] = summitVertex[v];

	return vertices;
}

GLuint* Pyramid::indices()
{
	GLuint* indices = new uint[getIndicesCount()];
	GLuint* baseIndices = base.indices();

	int numberVertices = getVerticesCount();
	int numberBaseSides = base.numberOfSides();
	int numberBaseIndices = base.getIndicesCount();

	int i = 0;
	for (int index = 0; index < numberBaseIndices; index++)
		indices[i++] = baseIndices[index];

	for (int index = 0; index < numberBaseSides; index++)
	{
		indices[i++] = index;
		indices[i++] = numberVertices - 1;
		indices[i++] = (index == numberBaseSides - 1) ? 0 : index + 1;
	}

	return indices;
}
