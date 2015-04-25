#include "grid.h"

#include <vector>

using namespace Shapes;

Grid::Grid(uint row, uint column)
	: row(row + 1), column(column + 1), 
	Shapes::SceneObject(std::to_string(row) + "x" + std::to_string(column) + " grid", GL_LINE)
{
}


Grid::~Grid()
{
}

GLfloat* Grid::vertices()
{
	if (m_vertices) return m_vertices;

	m_vertices = new float[Utilities::Vertex::VERTEX_SIZE * getVerticesCount()];

	int i = 0; // Vertice index

	for (int r = 0; r < row; r++)
	{
		Utilities::Vertex vertex = {
			Position(0.0f, r, 0.0f),
			Color(1.0f, 1.0f, 1.0f, 0.8f)
		};

		int test = 0;
		while (test < 2)
		{
			m_vertices[i++] = vertex.position.x;
			m_vertices[i++] = vertex.position.y;
			m_vertices[i++] = vertex.position.z;

			m_vertices[i++] = vertex.color.r;
			m_vertices[i++] = vertex.color.g;
			m_vertices[i++] = vertex.color.b;
			m_vertices[i++] = vertex.color.a;

			i++;
			i++;

			m_vertices[i++] = 0;
			m_vertices[i++] = 0;
			m_vertices[i++] = 1.0f;

			vertex.position.x = (column - 1);
			test++;
		}
	}

	for (int c = 0; c < column; c++)
	{
		Utilities::Vertex vertex = {
			Position(c, 0.0f, 0.0f),
			Color(1.0f, 1.0f, 1.0f, 0.8f)
		};

		int test = 0;
		while (test < 2)
		{
			m_vertices[i++] = vertex.position.x;
			m_vertices[i++] = vertex.position.y;
			m_vertices[i++] = vertex.position.z;

			m_vertices[i++] = vertex.color.r;
			m_vertices[i++] = vertex.color.g;
			m_vertices[i++] = vertex.color.b;
			m_vertices[i++] = vertex.color.a;

			i++;
			i++;
		
			m_vertices[i++] = 0;
			m_vertices[i++] = 0;
			m_vertices[i++] = 1.0f;

			vertex.position.y = (row - 1);
			test++;
		}
	}

	return m_vertices;
}

GLuint* Grid::indices()
{
	if (m_indices) return m_indices;

	m_indices = new uint[getIndicesCount()];

	for (int i = 0; i < getIndicesCount(); i++)
		m_indices[i] = i;

	return m_indices;
}
