#pragma once


#include "cameratransformationtrategy.h"

#include <glm.hpp>
#include <geometric.hpp>

class RotationCameraTransformationStrategy : public CameraTransformationStrategy
{
public:
	RotationCameraTransformationStrategy(Camera::GenericCamera* camera)
		: CameraTransformationStrategy(camera)
	{
	}

	virtual ~RotationCameraTransformationStrategy()
	{
	}

	virtual void transform(const glm::vec2& cursorTranslation)
	{
		float agressiveness = 0.8f;

		camera->yaw(agressiveness * -cursorTranslation.x);
		camera->pitch(agressiveness * cursorTranslation.y);
	}
};

