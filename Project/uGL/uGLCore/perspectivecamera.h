#pragma once

#include "genericcamera.h"

namespace Camera
{
	class PerspectiveCamera : public GenericCamera
	{
	public:
		static const int FOV_DEFAULT = 60.0f;
		static const int ASPECT_RATIO = (16.0f / 9.0f);

		PerspectiveCamera(float verticalFieldOfView = FOV_DEFAULT,
			float aspectRatio = ASPECT_RATIO);
		~PerspectiveCamera();

		virtual void changeZoomFactor(const glm::vec2& zoom);

		void changeFieldOfView(float verticalFieldOfView);
		void changeAspectRatio(int width, int height);

		virtual void contextUpdated(QOpenGLWidget* updatedContext);

		inline float getVerticalFieldOfView() const { return verticalFieldOfView; }

	protected:
		virtual void changeProjectionMatrix();

	private:
		float verticalFieldOfView;
		float aspectRatio;
	};
}

