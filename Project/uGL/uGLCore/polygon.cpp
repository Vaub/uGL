#include "polygon.h"
#include "uglutilities.h"

using namespace Shapes;

const long double PI = 3.141592653589793238L;

Polygon::Polygon(uint sides, float radius, glm::vec4 color, float height)
	: sides(sides), radius(radius), color(color), height(height), Shapes::SceneObject(std::to_string(sides) + "-sided polygon")
{
}


Polygon::~Polygon()
{
}

GLfloat* Polygon::vertices()
{
	m_vertices = new float[Utilities::Vertex::VERTEX_SIZE * getVerticesCount()];
	
	float angleRad;
	float valeur;
	int i = 0;
	for (int j = 0; j < sides; j++)
	{

		angleRad = (float)j*((2 * PI) / (float)sides);

		valeur =  radius * cos(angleRad);
		m_vertices[i++] = valeur;
		
		valeur =  radius * sin(angleRad);
		m_vertices[i++] = valeur;
		
		m_vertices[i++] = height;

		m_vertices[i++] = color[0];
		m_vertices[i++] = color[1];
		m_vertices[i++] = color[2];
		m_vertices[i++] = color[3];

		m_vertices[i++] = cos(angleRad) * 0.5f + 0.5f;
		m_vertices[i++] = sin(angleRad) * 0.5f + 0.5f;

		i++; i++; i++;
	}

	return m_vertices;
}

GLuint* Polygon::indices()
{
	if (m_indices) return m_indices;

	m_indices = new uint[getIndicesCount()];
	std::vector<uint> Test;

	int tri = 0;
	for (int i = 0; i < getIndicesCount(); i++)
	{
		if (i % 3 == 0)
		{
			m_indices[i] = 0;
			if (i != 0)
			tri++;
		}

		else
		{
			m_indices[i] = (i - (tri * 2));
		}
		Test.push_back(m_indices[i]);
	}
	
	return m_indices;
}