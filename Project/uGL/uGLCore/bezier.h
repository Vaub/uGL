#pragma once

#include <QtOpenGL>
#include "sceneobject.h"

using namespace std;

namespace Shapes
{
	class Bezier : public SceneObject
	{
		static const int DEFAULT_WIDTH = 1;

		static const int NB_FLOAT_PER_VERTICES = 7;
		static const int DEFAULT_NB_POINTS = 1000;

	public:
		Bezier(vector<glm::vec3> controlPoints, 
				int nbOfPoints = DEFAULT_NB_POINTS,
				glm::vec4 color = { 0, 1, 0, 1 });
		~Bezier();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return (this->curvePoints.size()); }
		virtual int getIndicesCount() const { return (this->curvePoints.size()); }

		glm::vec3* getPointAt(float index) const;
		vector<glm::vec3*> getCurvePoints();
		void modifyLineWidth(int width);

		virtual void render(
			int byteOffset,
			OpenGLContext* context,
			GLuint shaderProgramId,
			Camera::GenericCamera* camera);

	private:
		vector<glm::vec3> controlPoints;
		vector<glm::vec3*> curvePoints;

		glm::vec4 color;

		int nbOfPointsInACurve;
		int lineWidth = DEFAULT_WIDTH;

		void findCurvePoints();
		glm::vec3* getBezierPoint(int degree, int index, double paramT);
		double calculateLinearInterpolation(float coord0, float coord1, double paramT);
	};
}

