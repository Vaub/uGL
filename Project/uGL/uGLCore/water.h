#pragma once

#include "sceneobject.h"
#include <glm.hpp>

typedef unsigned int uint;


namespace Shapes
{
	class Water : public SceneObject
	{
	public:
		Water(glm::vec4 color = { 1, 1, 1, 1 });
		~Water();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return sides; }
		virtual int getIndicesCount() const { return m_indices.size(); }

		int numberOfSides() const { return sides; }

	private:
		uint sides = 4;
		glm::vec4 color;

		std::vector<GLfloat> m_vertices;
		std::vector<GLuint> m_indices;

		void initializeVertices();
		void initializeIndices();
	};


}
