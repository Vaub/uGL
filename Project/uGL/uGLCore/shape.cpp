#include "shape.h"

#include <memory>
#include <stdexcept>

using namespace std;

using namespace Shapes;
using namespace Utilities;

Shape::Shape(const std::vector<Utilities::Vertex>& vertices, const std::vector<GLuint>& indices, bool computeNormals)
	: m_vertices(vertices), m_indices(indices), Shapes::SceneObject("Shape")
{
	if (indices.size() == 0) {
		this->initVertices();
	}

	if (computeNormals) {
		this->computeNormals();
	}
}


Shape::~Shape()
{
}

float* Shape::vertices()
{
	if (getVerticesCount() == 0)
		throw std::invalid_argument("Can't render a shape with no vertices");

	float* verticesArray = new float[getVerticesCount() * Utilities::Vertex::VERTEX_SIZE];

	int indice = 0;
	for (int i = 0; i < getVerticesCount(); i++)
	{
		for (int j = 0; j < Vertex::VERTEX_SIZE; j++)
			verticesArray[indice++] = m_vertices[i][j];
	}

	return verticesArray;
}

GLuint* Shape::indices()
{
	if (m_indices.size() == 0)
		throw std::invalid_argument("Can't render a shape with no elements");

	GLuint* indicesArray = new GLuint[getIndicesCount()];
	
	for (unsigned int i = 0; i < getIndicesCount(); i++)
		indicesArray[i] = m_indices[i];

	return indicesArray;
}

void Shape::initVertices()
{
	m_indices = std::vector<GLuint>(getVerticesCount());
	for (int i = 0; i < getVerticesCount(); i++)
		m_indices[i] = i;
}

void Shape::computeNormals() {
	std::vector<glm::vec3> normals(m_vertices.size());

	for (int i = 0; i < m_indices.size(); i += 3) {
		int i1 = m_indices[i + 0], i2 = m_indices[i + 1], i3 = m_indices[i + 2];

		Utilities::Vertex* v1 = &m_vertices[i1];
		Utilities::Vertex* v2 = &m_vertices[i2];
		Utilities::Vertex* v3 = &m_vertices[i3];

		glm::vec3 normal = glm::cross(v2->position - v1->position, v3->position - v1->position);

		normal = glm::normalize(normal);
		normals[i1] += normal;
		normals[i2] += normal;
		normals[i3] += normal;
	}

	for (int i = 0; i < normals.size(); i++) {
		m_vertices[i].normal = glm::normalize(normals[i]);
	}
}
