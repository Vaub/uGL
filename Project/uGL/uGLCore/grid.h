#pragma once

#include "sceneobject.h"

typedef unsigned int uint;

namespace Shapes
{
	class Grid : public SceneObject
	{
	public:
		Grid(uint row, uint column);
		~Grid();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return 2 * (row + column); }
		virtual int getIndicesCount() const { return 2 * (row + column); }

		virtual void render(int offset, OpenGLContext* context, GLuint shaderProgram)
		{
			//context->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			context->glDrawElements(GL_LINES, getIndicesCount(), GL_UNSIGNED_INT, (void*)offset);

			//context->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	private:
		uint row,
			 column;

		GLfloat* m_vertices = 0;
		GLuint* m_indices = 0;
	};
}

