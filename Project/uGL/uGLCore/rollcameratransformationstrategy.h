#pragma once

#include "cameratransformationtrategy.h"

class RollCameraTransformationStrategy :
	public CameraTransformationStrategy
{
public:
	static const int ROTATION_SPEED = 0.8f;

	RollCameraTransformationStrategy(Camera::GenericCamera* camera)
		: CameraTransformationStrategy(camera)
	{
	}

	~RollCameraTransformationStrategy()
	{
	}

	void transform(const glm::vec2& cursorTranslation)
	{
		float agressiveness = 0.8f;

		camera->roll(agressiveness * cursorTranslation.x);
	}
};

