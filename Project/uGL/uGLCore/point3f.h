#pragma once

#include "uglutilities.h"

#include <ostream>

namespace Utilities
{

	class Point3f
	{
	public:

		Point3f(float x = 0, float y = 0, float z = 0)
		{
			setPosition(x, y, z);
		}

		Point3f(const Point3f& point)
			: m_x(point.m_x), m_y(point.m_y), m_z(point.m_z)
		{
		}

		~Point3f()
		{
		}

		void setPosition(float x, float y, float z)
		{
			m_x = uGLUtilities::OGLfloat(x);
			m_y = uGLUtilities::OGLfloat(y);
			m_z = uGLUtilities::OGLfloat(z);
		}

		float x() const { return m_x; }
		float y() const { return m_y; }
		float z() const { return m_z; }

		friend bool operator==(const Point3f& lhs, const Point3f& rhs)
		{
			return (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_z);
		}

		Point3f& operator=(const Point3f& rhs)
		{
			if (this != &rhs)
				setPosition(rhs.m_x, rhs.m_y, rhs.m_z);

			return *this;
		}

	private:
		float m_x,
			m_y,
			m_z;
	};

}

