#pragma once

#include "polygon.h"
#include <glm.hpp>

namespace Shapes
{

	class Circle : public Shapes::Polygon
	{
	public:


		Circle(float radius = 1.0f, glm::vec4 color = {1, 1, 1, 1.0f})
			: Shapes::Polygon(200, radius, color){}
		~Circle(){}

	};
}

