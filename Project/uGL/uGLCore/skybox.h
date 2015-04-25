#pragma once

#include "cube.h"
#include "shaderprogram.h"

namespace Shapes
{
	class Skybox : public Cube
	{
	public:
		Skybox(Shaders::ShaderProgram* skyboxShader);
		~Skybox();

		virtual void render(
			int byteOffset,
			OpenGLContext* context,
			GLuint shaderProgramId,
			Camera::GenericCamera* camera);

	private:
		Shaders::ShaderProgram* skyboxShader;
	};
}



