#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <QtGui\QOpenGLFunctions_3_3_Core>

#include "vertex.h"
#include <string>

#include "genericcamera.h"
#include "shaderprogram.h"
#include "texture.h"
#include "material.h"
#include "uglutilities.h"

typedef QOpenGLFunctions_3_3_Core OpenGLContext;

namespace Shapes
{
	class SceneObject
	{
	public:
		SceneObject(const std::string& name, GLenum renderingMode = GL_TRIANGLES);
		virtual ~SceneObject();

		virtual GLfloat* vertices() = 0;
		virtual GLuint* indices() = 0;

		virtual int getVerticesCount() const = 0;
		virtual int getIndicesCount() const = 0;

		virtual int getVerticesByteSize() const { return getVerticesCount() * sizeof(Utilities::Vertex); }
		virtual int getIndicesByteSize() const { return getIndicesCount() * sizeof(GLuint); }
		
		virtual glm::vec3 currentPosition() const { return position; };
		virtual void changePosition(const glm::vec3& position)
		{
			this->position = position;
		}

		virtual const glm::vec3& scaleFactor() const { return scale; }
		virtual void scaleShape(float scaleFactor);
		virtual void scaleShape(const glm::vec3& scaleFactor);
		virtual void rotate(const glm::vec3& eulersAngle);

		virtual void loadModel(OpenGLContext* context, GLuint shaderProgramId);

		/*
		 * Load the texture into the OpenGL context
		 * Sets the USE_TEXTURE_UNIFORM uniform on the shader if supported
		 */
		virtual void loadTexture(OpenGLContext* context, GLuint shaderProgramId);

		virtual void loadMaterial(OpenGLContext* context, GLuint shaderProgramId);

		/*
		 * Principal rendering method for the pipeline.
		 * Given the memory offset to draw from indices
		 * 
		 * In case of overriding :
		 *   - Should call its glDrawElements (or other)
		 *
		 * Parameters
		 *   - byteOffset : where to look in the buffer
		 *   - context : the opengl context
		 */
		virtual void render(
			int byteOffset, 
			OpenGLContext* context, 
			GLuint shaderProgramId, 
			Camera::GenericCamera* camera)
		{
			camera->applyCamera(shaderProgramId, context);

			loadModel(context, shaderProgramId);
			loadMaterial(context, shaderProgramId);
			loadTexture(context, shaderProgramId);

			context->glDrawElements(renderingMode, getIndicesCount(), GL_UNSIGNED_INT, (void*)byteOffset);
		}

		virtual Shaders::Material getMaterial() const { return material; }
		virtual void changeMaterial(const Shaders::Material material) {
			this->material = material;
		}

		virtual void setDrawAsMesh(bool drawAsMesh);
		virtual bool isDrawnAsMesh() const;
		
		virtual const std::string& getName() const;
		virtual void changeName(const std::string& name);

		virtual void changeTexture(Textures::Texture* texture);

	protected:
		std::string name;
		GLenum renderingMode;

		bool drawAsMesh;

		Shaders::Material material;
		Textures::Texture* texture = 0;

		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;

		glm::mat4 model;
		glm::mat3 normalMatrix;

		glm::mat4 createModel()
		{
			glm::mat4 model;
			return glm::translate(model, position) * (glm::mat4_cast(rotation) * model) * glm::scale(model, scale);
		}

		glm::mat3 createNormalMatrix()
		{

		}

		virtual void renderMesh(OpenGLContext* context) { context->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		
	};
}

