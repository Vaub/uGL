#pragma once

#include "cameratransformationtrategy.h"

class VertigoTransformationStrategy : public CameraTransformationStrategy
{

public:
	VertigoTransformationStrategy(Camera::GenericCamera* camera)
		: CameraTransformationStrategy(camera)
	{
	}

	~VertigoTransformationStrategy()
	{
	}

	virtual void transform(const glm::vec2& cursorTranslation)
	{
		glm::vec2 newZoom = camera->getZoom() - glm::vec2(0, cursorTranslation.y);

		if (newZoom.x > 0 && newZoom.y > 0) {
			camera->dolly(cursorTranslation.y);
			camera->changeZoomFactor(newZoom);
		}
	}
};

