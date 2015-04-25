#pragma once

#include <glm.hpp>

#include "genericcamera.h"

class CameraTransformationStrategy
{
public:
	CameraTransformationStrategy(Camera::GenericCamera* camera)
		: camera(camera)
	{
	}

	virtual ~CameraTransformationStrategy()
	{
	}

	virtual void transform(const glm::vec2& cursorTranslation) = 0;

protected:
	Camera::GenericCamera* camera;
};

