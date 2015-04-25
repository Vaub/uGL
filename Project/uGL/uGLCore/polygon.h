#pragma once

#include "sceneobject.h"
#include <glm.hpp>

typedef unsigned int uint;


namespace Shapes
{
	class Polygon : public SceneObject
	{
	public:
		Polygon(uint sides, float radius = 1.0f, glm::vec4 color = { 1, 1, 1, 1 }, float height = 0.0f);
		~Polygon();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return sides; }
		virtual int getIndicesCount() const { return (sides - 2) * 3; }

		int numberOfSides() const { return sides; }

	private:
		uint sides;
		float radius;
		float height;
		glm::vec4 color;

		GLfloat* m_vertices = 0;
		GLuint* m_indices = 0;
	};


}

