#pragma once

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <QtGui\qopenglfunctions_3_3_core.h>

#include "lightcolor.h"

typedef QOpenGLFunctions_3_3_Core OpenGLFunctions;

namespace Shaders 
{
	class Material
	{
	public:
		Material()
		{
		}

		Material(const LightColor& lightColor, float shineFactor)
			: lightColor(lightColor), shineFactor(shineFactor)
		{

		}

		void useMaterial(OpenGLFunctions* ogl, GLuint shaderProgramId)
		{
			GLuint uniAmbient = ogl->glGetUniformLocation(shaderProgramId, "material.ambient");
			GLuint uniDiffuse = ogl->glGetUniformLocation(shaderProgramId, "material.diffuse");
			GLuint uniSpecular = ogl->glGetUniformLocation(shaderProgramId, "material.specular");
			GLuint uniShineFactor = ogl->glGetUniformLocation(shaderProgramId, "material.shineFactor");

			ogl->glUniform3fv(uniAmbient, 1, glm::value_ptr(lightColor.ambient));
			ogl->glUniform3fv(uniDiffuse, 1, glm::value_ptr(lightColor.diffuse));
			ogl->glUniform3fv(uniSpecular, 1, glm::value_ptr(lightColor.specular));
			ogl->glUniform1f(uniShineFactor, shineFactor);
		}

		static Material whiteRubber() {
			return Material(
				LightColor{ 
					glm::vec3(0.05f, 0.05f, 0.05f),
					glm::vec3(0.50f, 0.50f, 0.50f),
					glm::vec3(0.70f, 0.70f, 0.70f) },
				10.0f
			);
		}

		static Material whitePlastic() {
			return Material(
				LightColor{ 
					glm::vec3(0, 0, 0),
					glm::vec3(0.55f, 0.55f, 0.55f),
					glm::vec3(0.70f, 0.70f, 0.70f) },
				32.0f
			);
		}

		static Material brass() {
			return Material(
				LightColor{
					glm::vec3(0.329412f, 0.223529f, 0.027451f),
					glm::vec3(0.780392f, 0.568627f, 0.113725f),
					glm::vec3(0.992157f, 0.941176f, 0.807843f) },
				27.8974f
			);
		}

		static Material bronze() {
			return Material(
				LightColor{
					glm::vec3(0.2125f, 0.1275f, 0.054f),
					glm::vec3(0.714f, 0.4284f, 0.18144f),
					glm::vec3(0.393548f, 0.271906f, 0.166721f) },
				25.6f
			);
		}

		static Material ruby() {
			return Material(
				LightColor{
					glm::vec3(0.1745f, 0.01175f, 0.01175f),
					glm::vec3(0.61424f, 0.04136f, 0.04136f),
					glm::vec3(0.727811f, 0.626959f, 0.626959f) },
				76.8f
			);
		}

		static Material chrome() {
			return Material(
				LightColor{
					glm::vec3(0.25f, 0.25f, 0.25f),
					glm::vec3(0.40f, 0.40f, 0.40f),
					glm::vec3(0.774597f, 0.774597f, 0.774597f) },
				76.8f
			);
		}

		LightColor lightColor;
		float shineFactor;
	};
}

