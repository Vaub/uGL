#pragma once

#include <string>

#include "light.h"
#include <QtGui/qopenglfunctions.h>

typedef QOpenGLFunctions_3_3_Core OpenGLFunctions;

namespace Shaders
{
	class ShaderProgram
	{
	public:
		ShaderProgram(OpenGLFunctions* context,
			const std::string& name,
			const std::string& vertexShaderFile,
			const std::string& fragmentShaderFile,
			const std::string& geometricShaderFile = "");

		~ShaderProgram();

		void addLight(Light* light);

		void use();
		uint getProgramId() const { return shaderProgramId; };

	private:
		OpenGLFunctions* ogl;

		std::string name;
		std::vector<Light*> lights;

		GLuint vertexShaderId;
		GLuint fragmentShaderId;
		GLuint geometricShaderId;

		GLuint shaderProgramId;
		GLuint addShader(const std::string& file, GLenum shaderType);

		void compileShaderProgram(bool withGeometricShader = false);

		static std::string readShaderFile(const char* file);
	};
}

