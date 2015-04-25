#pragma once

#include "cameratransformationtrategy.h"

class DepthCameraTransformationStrategy :
	public CameraTransformationStrategy
{
public:

	DepthCameraTransformationStrategy(Camera::GenericCamera* camera)
		: CameraTransformationStrategy(camera)
	{
	}

	~DepthCameraTransformationStrategy()
	{
	}

	virtual void transform(const glm::vec2& cursorTranslation)
	{
		camera->dolly(cursorTranslation.y);
	}
};

