#include "genericcamera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/transform.hpp>

using namespace Camera;

GenericCamera::GenericCamera()
	: position(0, 0, 5.0f), eye(0, 0, -5.0f), up(0.0f, -1.0f, 0.0f), zNear(ZNEAR_DEFAULT), zFar(ZFAR_DEFAULT)
{
	eye = glm::normalize(eye);
}


GenericCamera::~GenericCamera()
{
}

void GenericCamera::applyCamera(GLuint shaderProgram, OpenGLContext* context)
{
	GLuint uniView = context->glGetUniformLocation(shaderProgram, "view");
	GLuint uniProj = context->glGetUniformLocation(shaderProgram, "proj");
	GLuint uniCamPos = context->glGetUniformLocation(shaderProgram, "viewPosition");

	context->glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(createView()));
	context->glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projection));

	context->glUniform3fv(uniCamPos, 1, glm::value_ptr(position));
}

void GenericCamera::pan(const glm::vec2& speed)
{
	glm::vec2 panSpeed = MOUSE_ACCELERATION * speed;

	glm::vec3 side = glm::cross(eye, up);

	position += panSpeed.x * glm::normalize(side);
	position += panSpeed.y * glm::normalize(up);
}

void GenericCamera::dolly(float speed)
{
	position += speed * eye;
}

void GenericCamera::yaw(float angleInRadians)
{
	rotate(angleInRadians, up);
}

void GenericCamera::pitch(float angleInRadians)
{
	rotate(angleInRadians, glm::cross(eye, up));
}

void GenericCamera::roll(float angleInRadians)
{
	glm::vec4 upRotated = glm::rotate(angleInRadians, glm::normalize(eye)) * glm::vec4(up, 1.0f);
	up = glm::vec3(upRotated);
}

void GenericCamera::rotate(float angleInRadians, const glm::vec3& axis)
{
	glm::vec4 eyeRotated = glm::rotate(angleInRadians, glm::normalize(axis)) * glm::vec4(eye, 1.0f); // Need padding
	eye = glm::vec3(eyeRotated);
}

void GenericCamera::changeFarAndNearField(float zNear, float zFar)
{
	if (!validateZNearZFarValues(zNear, zFar))
		throw std::invalid_argument("zNear or zFar were not the right value.");

	this->zNear = zNear;
	this->zFar = zFar;

	changeProjectionMatrix();
}

glm::mat4 GenericCamera::createView()
{
	return glm::lookAt(position, position + eye, up);
}

bool GenericCamera::validateZNearZFarValues(float zNear, float zFar)
{
	return ((zNear >= 0 && zFar >= 0) && (zNear < zFar));
}