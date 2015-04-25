#include "shaderprogram.h"

#include <fstream>
#include <QtGui\qopenglfunctions_3_3_core.h>

using namespace Shaders;

ShaderProgram::ShaderProgram(OpenGLFunctions* context,
	const std::string& name, 
	const std::string& vertexShaderFile, 
	const std::string& fragmentShaderFile,
	const std::string& geometricShaderFile)
	: name(name), ogl(context)
{
	vertexShaderId = addShader(vertexShaderFile, GL_VERTEX_SHADER);
	fragmentShaderId = addShader(fragmentShaderFile, GL_FRAGMENT_SHADER);
	
	if (!geometricShaderFile.empty()) {
		geometricShaderId = addShader(geometricShaderFile, GL_GEOMETRY_SHADER);
	}

	compileShaderProgram(!geometricShaderFile.empty());
}


ShaderProgram::~ShaderProgram()
{
	//ogl->glDeleteShader(vertexShaderId);
	//ogl->glDeleteShader(fragmentShaderId);
}

void ShaderProgram::use() {
	ogl->glUseProgram(shaderProgramId);

	for (const auto& light : lights) {
		light->loadLight(ogl, shaderProgramId);
	}
}

void ShaderProgram::addLight(Light* light)
{
	lights.push_back(light);
}

GLuint ShaderProgram::addShader(const std::string& file, GLenum shaderType)
{
	GLuint shaderId = ogl->glCreateShader(shaderType);

	const GLchar* adapter[1];
	std::string shaderCode = readShaderFile(file.c_str());

	adapter[0] = shaderCode.c_str();
	ogl->glShaderSource(shaderId, 1, adapter, 0);

	ogl->glCompileShader(shaderId);

	GLint isCompiled = 0;
	ogl->glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		ogl->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		ogl->glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

		ogl->glDeleteShader(shaderId);
		throw std::invalid_argument(&infoLog[0]);
	}

	return shaderId;
}

void ShaderProgram::compileShaderProgram(bool withGeometricShader) {
	shaderProgramId = ogl->glCreateProgram();

	ogl->glAttachShader(shaderProgramId, vertexShaderId);
	ogl->glAttachShader(shaderProgramId, fragmentShaderId);

	if (withGeometricShader) {
		ogl->glAttachShader(shaderProgramId, geometricShaderId);
	}

	ogl->glLinkProgram(shaderProgramId);
}

std::string ShaderProgram::readShaderFile(const char* file)
{
	std::ifstream input(file);
	if (!input.good())
		throw std::invalid_argument("Can't reader shader.");

	return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}
