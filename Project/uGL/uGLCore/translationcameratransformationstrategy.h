#pragma once

#include "cameratransformationtrategy.h"

class TranslationCameraTransformationStrategy :
	public CameraTransformationStrategy
{
public:

	TranslationCameraTransformationStrategy(Camera::GenericCamera* camera)
		: CameraTransformationStrategy(camera)
	{
	}

	~TranslationCameraTransformationStrategy()
	{
	}

	void transform(const glm::vec2& cursorTranslation)
	{
		camera->pan(cursorTranslation);
	}
};

