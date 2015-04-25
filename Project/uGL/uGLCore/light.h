#pragma once

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <QtGui\qopenglfunctions_3_3_core.h>

#include "lightcolor.h"

typedef glm::vec4 Color;
typedef QOpenGLFunctions_3_3_Core OpenGLFunctions;

namespace Shaders {

	class Light
	{
	public:

		Light(const Shaders::LightColor& lightColor, const std::string& name = "light")
			: lightColor(lightColor), name(name)
		{
		}

		virtual ~Light()
		{
		}

		const std::string& getLightName() const { return name; }

		virtual void loadLight(OpenGLFunctions* ogl, GLuint shaderProgramId)
		{
			GLuint uniAmbient = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "ambient").c_str());
			GLuint uniDiffuse = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "diffuse").c_str());
			GLuint uniSpecular = ogl->glGetUniformLocation(shaderProgramId, createParameter(getLightName(), "specular").c_str());

			ogl->glUniform3fv(uniAmbient, 1, glm::value_ptr(lightColor.ambient));
			ogl->glUniform3fv(uniDiffuse, 1, glm::value_ptr(lightColor.diffuse));
			ogl->glUniform3fv(uniSpecular, 1, glm::value_ptr(lightColor.specular));
		}

		static std::string createParameter(const std::string& name, const std::string& parameter) 
		{
			return (name + "." + parameter);
		}

	public:
		std::string name;

		Shaders::Light::LightColor lightColor;
	};
}

