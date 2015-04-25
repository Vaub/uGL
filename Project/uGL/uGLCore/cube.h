#pragma once

#include "sceneobject.h"
#include <vector>
#include <glm.hpp>

typedef unsigned int uint;
typedef glm::vec4 Color;

namespace Shapes
{
	class Cube : public SceneObject
	{
	public:
		Cube();
		~Cube();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return m_vertices.size(); }
		virtual int getIndicesCount() const { return m_indices.size(); }

		void colorize(const Color& color);

	private:
		void setDefaultCubeVertices();

		std::vector<Utilities::Vertex> m_vertices;
		std::vector<GLuint> m_indices;

		glm::vec4 m_color;
	};
}




