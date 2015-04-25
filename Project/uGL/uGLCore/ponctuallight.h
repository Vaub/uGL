#pragma once

#include "light.h"

namespace Shaders {

	class PonctualLight : public Light
	{
	public:

		PonctualLight(const glm::vec3& position, const LightColor& lightColor, const std::string& name = "light")
			: Shaders::Light(lightColor, name), position(position)
		{
		}

		~PonctualLight()
		{
		}

		virtual void loadLight(OpenGLFunctions* ogl, GLuint shaderProgramId)
		{
			Shaders::Light::loadLight(ogl, shaderProgramId);

			GLuint uniDirection = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "position").c_str());
			ogl->glUniform3fv(uniDirection, 1, glm::value_ptr(position));
		}

	public:
		glm::vec3 position;
	};

}
