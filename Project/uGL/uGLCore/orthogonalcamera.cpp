#include "orthogonalcamera.h"

using namespace Camera;

OrthogonalCamera::OrthogonalCamera(float left, float right, float bottom, float top, float zNear, float zFar)
:left(left), right(right), bottom(bottom), top(top)
{
	this->zNear = zNear;
	this->zFar = zFar;

	changeZoomFactor(glm::vec2(1.0f, 1.0f));

	changeProjectionMatrix();
}

OrthogonalCamera::~OrthogonalCamera()
{
}

void OrthogonalCamera::changeProjectionMatrix()
{
	projection = glm::ortho(-left / DECREASE_BOUNDS, right / DECREASE_BOUNDS,
							-bottom / DECREASE_BOUNDS, top / DECREASE_BOUNDS,
							zNear, zFar);
}

void OrthogonalCamera::changeZoomFactor(const glm::vec2& zoom)
{
	if (!validateZoomFactor(zoom))
		throw std::invalid_argument("Zoom factors cannot be negative!");

	changeProjectionMatrix();
}

void OrthogonalCamera::contextUpdated(QOpenGLWidget* updatedContext)
{
	left = updatedContext->width();
	right = updatedContext->width();
	bottom = updatedContext->height();
	top = updatedContext->height();

	changeProjectionMatrix();
}

void OrthogonalCamera::setParameters(float left, float right, float bottom, float top)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;

	changeProjectionMatrix();
}

void OrthogonalCamera::setDefaults()
{
	left = WIDTH_DEFAULT;
	right = WIDTH_DEFAULT;
	bottom = HEIGHT_DEFAULT;
	top = HEIGHT_DEFAULT;

	zNear = ZNEAR_DEFAULT;
	zFar = ZFAR_DEFAULT;

	changeProjectionMatrix();
}

float OrthogonalCamera::getLeft()
{
	return left;
}

float OrthogonalCamera::getRight()
{
	return right;
}

float OrthogonalCamera::getBottom()
{
	return bottom;
}

float OrthogonalCamera::getTop()
{
	return top;
}