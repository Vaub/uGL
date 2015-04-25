#include "cube.h"

using namespace Shapes;

using Utilities::Vertex;

Cube::Cube()
	: Shapes::SceneObject("Cube")
{
	setDefaultCubeVertices();
}


Cube::~Cube()
{
}

void Cube::colorize(const Color& color)
{
	for (int i = 0; i < getVerticesCount(); i++)
		m_vertices[i].color = color;
}

GLfloat* Cube::vertices()
{
	float* verticesArray = new float[getVerticesCount() * Utilities::Vertex::VERTEX_SIZE];

	int indice = 0;
	for (int i = 0; i < getVerticesCount(); i++)
	{
		for (int j = 0; j < Vertex::VERTEX_SIZE; j++)
			verticesArray[indice++] = m_vertices[i][j];
	}

	return verticesArray;
}

GLuint* Cube::indices()
{
	return &m_indices[0];
}

void Cube::setDefaultCubeVertices()
{
	glm::vec4 color = glm::vec4(1, 1, 1, 1);

	float x = 1.0f, y = 1.0f, z = 1.0f;
	using namespace Utilities;

	m_vertices = {
		Vertex{ glm::vec3(-x, +y, -z), color },
		Vertex{ glm::vec3(-x, -y, -z), color },
		Vertex{ glm::vec3(+x, -y, -z), color },
		Vertex{ glm::vec3(+x, +y, +z), color },
		Vertex{ glm::vec3(-x, -y, +z), color },
		Vertex{ glm::vec3(-x, +y, +z), color },
		Vertex{ glm::vec3(+x, -y, +z), color },
		Vertex{ glm::vec3(+x, +y, -z), color }
	};

	m_indices = {
		0, 1, 2, 2, 3, 0,
		4, 1, 0, 0, 5, 4,
		2, 6, 3, 3, 7, 2,
		4, 5, 3, 3, 6, 4,
		0, 7, 3, 3, 5, 0,
		1, 4, 2, 2, 4, 6
	};
}
