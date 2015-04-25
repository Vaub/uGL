#include "triangle.h"

using namespace Shapes;

Triangle::Triangle(glm::vec2 vector1, glm::vec2 vector2, glm::vec2 vector3, glm::vec4 color, float height)
	: vector1(vector1), vector2(vector2), vector3(vector3), color(color), height(height), Shapes::SceneObject("Triangle")
{
}


Triangle::~Triangle()
{
}

GLfloat* Triangle::vertices()
{
	m_vertices = new float[Utilities::Vertex::VERTEX_SIZE * getVerticesCount()];

	
	Utilities::Vertex v1 = { glm::vec3(vector1,height), color };
	Utilities::Vertex v2 = { glm::vec3(vector2, height), color };
	Utilities::Vertex v3 = { glm::vec3(vector3, height), color };
	Utilities::Vertex v[] = { v1, v2, v3 };
	
	int i = 0;
	for (int j = 0; j < 3; j++)
	{
		m_vertices[i++] = v[j].position.x;
		m_vertices[i++] = v[j].position.y;
		m_vertices[i++] = v[j].position.z;

		m_vertices[i++] = v[j].color.r;
		m_vertices[i++] = v[j].color.g;
		m_vertices[i++] = v[j].color.b;
		m_vertices[i++] = v[j].color.a;
	}

	return m_vertices;
}

GLuint* Triangle::indices()
{
	
	if (m_indices) return m_indices;
	
		m_indices = new uint[getIndicesCount()];

		for (int i = 0; i < 3; i++)
		{
			m_indices[i] = i;
		}

		return m_indices;
}
