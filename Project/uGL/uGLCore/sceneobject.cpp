#include "sceneobject.h"

using namespace Shapes;

SceneObject::SceneObject(const std::string& name, GLenum renderingMode)
	: name(name), renderingMode(renderingMode)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	this->texture = 0;
	this->material = Shaders::Material::whitePlastic();

	this->drawAsMesh = false;
}

SceneObject::~SceneObject()
{

}

const std::string& SceneObject::getName() const { return name; }
void SceneObject::changeName(const std::string& name)
{
	this->name = name;
}

void SceneObject::setDrawAsMesh(bool drawAsMesh) { this->drawAsMesh = drawAsMesh; }
bool SceneObject::isDrawnAsMesh() const { return drawAsMesh; }

void SceneObject::loadTexture(OpenGLContext* context, GLuint shaderProgramId)
{

	bool useTexture = (texture) ? texture->useTexture(shaderProgramId) : false;
	context->glUniform1i(context->glGetUniformLocation(shaderProgramId, "useTexture"), useTexture);
}

void SceneObject::loadMaterial(OpenGLContext* context, GLuint shaderProgramId)
{
	material.useMaterial(context, shaderProgramId);
}

void SceneObject::changeTexture(Textures::Texture* texture)
{
	this->texture = texture;
}

void SceneObject::scaleShape(float scaleFactor)
{
	scaleShape(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
}

void SceneObject::scaleShape(const glm::vec3& scaleFactor)
{
	this->scale = scaleFactor * glm::vec3(1.0f, 1.0f, 1.0f);
}

void SceneObject::rotate(const glm::vec3& eulersAngle)
{
	this->rotation = Utilities::uGLUtilities::eulersToQuat(glm::radians(eulersAngle));
}

void SceneObject::loadModel(OpenGLContext* ogl, GLuint shaderProgramId)
{
	GLuint uniModel = ogl->glGetUniformLocation(shaderProgramId, "model");
	GLuint uniNormalMatrix = ogl->glGetUniformLocation(shaderProgramId, "normalMatrix");

	glm::mat4 model = createModel();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

	ogl->glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	ogl->glUniformMatrix3fv(uniNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

