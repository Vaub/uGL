#pragma once

#include <vector>

#include <QtOpenGL>

#include "sceneobject.h"
#include "vertex.h"
#include "uglutilities.h"

namespace Shapes
{
	class Shape : public SceneObject
	{
	public:
		Shape(const std::vector<Utilities::Vertex>& vertices, 
			const std::vector<GLuint>& indices,
			bool computeNormals = false);

		~Shape();

		virtual float* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return m_vertices.size(); }
		virtual int getIndicesCount() const { return m_indices.size(); }

	protected:
		std::vector<Utilities::Vertex> m_vertices;
		std::vector<GLuint> m_indices;

	private:
		void initVertices();
		void computeNormals();
	};
}

