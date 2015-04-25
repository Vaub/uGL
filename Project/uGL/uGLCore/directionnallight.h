#pragma once

#include "light.h"

namespace Shaders
{
	class DirectionnalLight : public Shaders::Light
	{
	public:

		DirectionnalLight(const glm::vec3& direction, const Shaders::LightColor& lightColor, const std::string& name = "light")
			: Shaders::Light(lightColor, name), direction(direction)
		{
		}

		~DirectionnalLight()
		{
		}

		virtual void loadLight(OpenGLFunctions* ogl, GLuint shaderProgramId)
		{
			Shaders::Light::loadLight(ogl, shaderProgramId);

			std::string dir = createParameter(getLightName(), "direction");
			GLuint uniDirection = ogl->glGetUniformLocation(shaderProgramId, dir.c_str());
			ogl->glUniform3fv(uniDirection, 1, glm::value_ptr(direction));
		}

	private:
		glm::vec3 direction;
	};
}

