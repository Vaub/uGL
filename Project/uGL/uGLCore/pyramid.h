#pragma once

#include "shape.h"

#include "polygon.h"

typedef unsigned int uint;

namespace Shapes
{
	class Pyramid : public SceneObject
	{
	public:
		Pyramid(uint numberOfSides, float radius = 0.5f, float height = 1.0f);
		~Pyramid();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return base.getVerticesCount() + 1; }
		virtual int getIndicesCount() const { return base.getIndicesCount() + (base.numberOfSides() * 3); }

	private:
		Polygon base;
		Utilities::Vertex summitVertex;
	};
}

