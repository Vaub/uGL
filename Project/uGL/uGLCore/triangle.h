#pragma once

#include "sceneobject.h"
#include <glm.hpp>


typedef unsigned int uint;

namespace Shapes
{
	class Triangle : public SceneObject
	{
	public:
		Triangle(glm::vec2 vector1 = { 0, 0.5f },
			glm::vec2 vector2 = { -0.5f, -0.5f }, 
			glm::vec2 vector3 = { 0.5f, -0.5f }, 
			glm::vec4 color = { 1, 1, 1, 1 },
			float height = 0.0f);
		~Triangle();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return 3;}
		virtual int getIndicesCount() const { return 3;}



		virtual void render(int offset, OpenGLContext* context, glm::mat4& model, GLuint shaderProgram)
		{
			context->glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, (void*)offset);
		}

	
	private:
		glm::vec2 vector1;
		glm::vec2 vector2;
		glm::vec2 vector3;
		glm::vec4 color;
		float height;

		GLfloat* m_vertices = 0;
		GLuint* m_indices = 0;
	};

}