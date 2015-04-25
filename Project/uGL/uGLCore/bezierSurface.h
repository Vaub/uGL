#pragma once

#include "bezier.h"
#include "sceneobject.h"

#include <QtOpenGL>
#include <glm.hpp>

namespace Shapes
{
	class BezierSurface : public SceneObject
	{
		static const int DEFAULT_COUNT = 10;

		const int DEFAULT_NB_POINTS_IN_A_CURVE = 1000;
		const int MIN_NB_POINTS = 500;

	public:
		BezierSurface(std::vector<glm::vec3> controlPoints,
						int nbOfControlPointsInACurve,
						int numberOfColumn = DEFAULT_COUNT,
						int numberOfRow = DEFAULT_COUNT,
						glm::vec4 color = { 0, 0, 1, 1 });
		~BezierSurface();

		virtual GLfloat* vertices();
		virtual GLuint* indices();

		virtual int getVerticesCount() const { return ((numberOfColumn + 1) * (numberOfRow + 1)); }
		virtual int getIndicesCount() const { return  ((2*(numberOfRow+1) + 2*(numberOfRow))*numberOfColumn); }

	private:
		glm::vec4 color;
		std::vector<glm::vec3> pointList;
		std::vector<glm::vec3> controlPoints;
		std::vector<Bezier> initialBezierCurves;

		int nbOfControlPointsInACurve;
		int numberOfColumn;
		int numberOfRow;

		int findNumberOfPoints(int count);
		void constructInitialBezierCurves(int nbOfPointsColumn);
		void getTrianglePoints();
	};
}

