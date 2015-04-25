#pragma once

#include "genericcamera.h"
#include <gtc/matrix_transform.hpp>

namespace Camera
{
	class OrthogonalCamera : public GenericCamera
	{

	public:
		static const int WIDTH_DEFAULT = 800;
		static const int HEIGHT_DEFAULT = 600;
		static const int ZNEAR_DEFAULT = 1;
		static const int ZFAR_DEFAULT = 1;

		static const int DECREASE_BOUNDS = 100;


		OrthogonalCamera(float left = WIDTH_DEFAULT, float right = WIDTH_DEFAULT,
			float bottom = HEIGHT_DEFAULT, float top = HEIGHT_DEFAULT,
			float zNear = ZNEAR_DEFAULT, float zFar = ZFAR_DEFAULT);
		~OrthogonalCamera();

		virtual void changeZoomFactor(const glm::vec2& zoom);

		virtual void contextUpdated(QOpenGLWidget* updatedContext);

		void setParameters(float left, float right, float bottom, float top);
		void setDefaults();

		float getLeft();
		float getRight();
		float getBottom();
		float getTop();

	protected:
		virtual void changeProjectionMatrix();

	private:
		float left;
		float right;
		float bottom;
		float top;
	};
}

