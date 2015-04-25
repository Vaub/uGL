#pragma once

#include "light.h"
#include "lightattenuation.h"

namespace Shaders {

	class Spotlight : public Light
	{
	public:

		Spotlight(const glm::vec3& position, 
			const glm::vec3& direction, 
			float cutOff, float outerCutOff, 
			LightAttenuation attenuation, 
			LightColor color,
			const std::string& name = "light")
			: Light(color, name), position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), attenuation(attenuation)
		{
		}

		~Spotlight()
		{
		}

		virtual void loadLight(OpenGLFunctions* ogl, GLuint shaderProgramId)
		{
			Shaders::Light::loadLight(ogl, shaderProgramId);

			GLuint uniPosition = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "position").c_str());
			ogl->glUniform3fv(uniPosition, 1, glm::value_ptr(position));

			GLuint uniDirection = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "direction").c_str());
			ogl->glUniform3fv(uniDirection, 1, glm::value_ptr(direction));

			GLuint uniCutOff = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "cutOff").c_str());
			GLuint uniOuterCutOff = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "outerCutOff").c_str());
			ogl->glUniform1f(uniOuterCutOff, cutOff);
			ogl->glUniform1f(uniOuterCutOff, outerCutOff);

			GLuint uniAttenuation = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "attenuation").c_str());
			ogl->glUniform3f(uniAttenuation, attenuation.constant, attenuation.linear, attenuation.quadratic);
		}

	private:
		glm::vec3 position;
		glm::vec3 direction;
		
		float cutOff;
		float outerCutOff;

		LightAttenuation attenuation;
	};

}