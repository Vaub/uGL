#include "perspectivecamera.h"

#include <stdexcept>
#include <gtc/matrix_transform.hpp>

using namespace Camera;

PerspectiveCamera::PerspectiveCamera(float verticalFieldOfView, float aspectRatio)
	: verticalFieldOfView(verticalFieldOfView), aspectRatio(aspectRatio)
{
	changeZoomFactor(glm::vec2(1.0f, 1.0f));

	changeProjectionMatrix();
}


PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::changeZoomFactor(const glm::vec2& zoom)
{
	if (!validateZoomFactor(zoom))
		throw std::invalid_argument("Zoom factors cannot be negative!");

	this->zoom = zoom;

	verticalFieldOfView = 2 * std::atan(1.0f / zoom.y);

	changeProjectionMatrix();
}

void PerspectiveCamera::changeFieldOfView(float verticalFieldOfView)
{
	this->verticalFieldOfView = verticalFieldOfView;
	changeProjectionMatrix();
}

void PerspectiveCamera::changeAspectRatio(int width, int height)
{
	if (width > 0 && height > 0)
		this->aspectRatio = (float)width / (float)height;
	else
		this->aspectRatio = (float)16 / (float)9;

	changeProjectionMatrix();
}

void PerspectiveCamera::changeProjectionMatrix()
{
	projection = glm::perspective(verticalFieldOfView, aspectRatio, zNear, zFar);
}


void PerspectiveCamera::contextUpdated(QOpenGLWidget* updatedContext)
{
	changeAspectRatio(updatedContext->width(), updatedContext->height());
}