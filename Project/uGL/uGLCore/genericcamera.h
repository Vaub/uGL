#pragma once

#include <glm.hpp>

#include <QtOpenGl>
#include <QtGui\QOpenGLFunctions_3_3_Core>

typedef QOpenGLFunctions_3_3_Core OpenGLContext;

namespace Camera
{

	class GenericCamera
	{
	public:
		const float MOUSE_ACCELERATION = 5.0f;

		const float ZNEAR_DEFAULT = 0.1f;
		const float ZFAR_DEFAULT = 100.0f;

		GenericCamera();
		~GenericCamera();

		virtual void applyCamera(GLuint shaderProgram, OpenGLContext* context);

		virtual void changeZoomFactor(const glm::vec2& zoom) = 0;
		
		virtual void pan(const glm::vec2& speed);
		virtual void dolly(float speed);

		virtual void yaw(float angleInRadians);
		virtual void pitch(float angleInRadians);
		virtual void roll(float angleInRadians);

		virtual void contextUpdated(QOpenGLWidget* updatedContext) = 0;

		void changeFarAndNearField(float zNear, float zFar);

		inline virtual glm::vec2 getZoom() { return glm::vec2(zoom.x, zoom.y); }
		inline float getNearField() const { return zNear; }
		inline float getFarField() const { return zFar; }

	protected:
		glm::vec2 zoom;
		glm::mat4 projection;

		float zNear;
		float zFar;

		virtual void rotate(float angleInRadians, const glm::vec3& axis);
		virtual void changeProjectionMatrix() = 0;

		inline bool validateZoomFactor(const glm::vec2& zoomFactor) const { return (zoomFactor.x > 0 && zoomFactor.y > 0); }

	private:

		glm::vec3 position;
		glm::vec3 eye;
		glm::vec3 up;

		glm::mat4 createView();
		bool validateZNearZFarValues(float zNear, float zFar);
	};

}

