#include "water.h"
#include "uglutilities.h"

using namespace Shapes;

Water::Water(glm::vec4 color)
:color(color), Shapes::SceneObject("Water")
{
	initializeVertices();
	initializeIndices();
}

Water::~Water()
{
}

GLfloat* Water::vertices()
{
	return &m_vertices[0];
}

GLuint* Water::indices()
{
	return &m_indices[0];
}

void Water::initializeVertices()
{
	int i = 0;
	//Bottom left
	m_vertices.push_back(-0.5f);
	m_vertices.push_back(-0.5f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(color.r);
	m_vertices.push_back(color.g);
	m_vertices.push_back(color.b);
	m_vertices.push_back(color.a);

	m_vertices.push_back(0.0f);//Texture coordinates
	m_vertices.push_back(1.0f);

	m_vertices.push_back(0.0f); m_vertices.push_back(0.0f); m_vertices.push_back(1.0f);

	//Top left
	m_vertices.push_back(-0.5f);
	m_vertices.push_back(0.5f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(color.r);
	m_vertices.push_back(color.g);
	m_vertices.push_back(color.b);
	m_vertices.push_back(color.a);

	m_vertices.push_back(0.0f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(0.0f); m_vertices.push_back(0.0f); m_vertices.push_back(1.0f);

	//Top right
	m_vertices.push_back(0.5f);
	m_vertices.push_back(0.5f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(color.r);
	m_vertices.push_back(color.g);
	m_vertices.push_back(color.b);
	m_vertices.push_back(color.a);

	m_vertices.push_back(1.0f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(0.0f); m_vertices.push_back(0.0f); m_vertices.push_back(1.0f);

	//Bottom right
	m_vertices.push_back(0.5f);
	m_vertices.push_back(-0.5f);
	m_vertices.push_back(0.0f);

	m_vertices.push_back(color.r);
	m_vertices.push_back(color.g);
	m_vertices.push_back(color.b);
	m_vertices.push_back(color.a);

	m_vertices.push_back(1.0f);
	m_vertices.push_back(1.0f);

	m_vertices.push_back(0.0f); m_vertices.push_back(0.0f); m_vertices.push_back(1.0f);
}

void Water::initializeIndices()
{
	m_indices = { 
		0, 1, 2,
		0, 2, 3
	};
}