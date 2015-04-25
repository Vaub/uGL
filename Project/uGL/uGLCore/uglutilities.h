#pragma once

#include <math.h>
#include <gtc/quaternion.hpp>

namespace Utilities
{
	class uGLUtilities
	{
	public:
		static double PI() { return 3.14159265358979323846; }

		static float OGLfloat(float number)
		{
			return (number < -1) ? -1 : (number > 1) ? 1 : number;
		}

		static glm::quat eulersToQuat(const glm::vec3& angles) {
			glm::vec3 c = cos(angles / 2.0f);
			glm::vec3 s = sin(angles / 2.0f);

			glm::quat quaternion = glm::quat {
				c.x*c.y*c.z - s.x*s.y*s.z,
				s.x*s.y*c.z + c.x*c.y*s.z,
				s.x*c.y*c.z + c.x*s.y*s.z,
				c.x*s.y*c.z - s.x*c.y*s.z
			};

			return quaternion;
		}
	};
}

