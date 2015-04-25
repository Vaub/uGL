#pragma once

#include "uglutilities.h"

namespace Utilities
{

	class Color4f
	{
	public:

		Color4f(float red = 1, float green = 1, float blue = 1, float alpha = 1)
		{
			setColor(red, green, blue, alpha);
		}

		Color4f(const Color4f& color)
			: m_red(color.m_red), m_green(color.m_green), m_blue(color.m_blue), m_alpha(color.m_alpha)
		{
		}

		~Color4f()
		{
		}

		void setRed(float red)
		{
			m_red = uGLUtilities::OGLfloat(red);
		}

		void setGreen(float green)
		{
			m_green = uGLUtilities::OGLfloat(green);
		}

		void setBlue(float blue)
		{
			m_blue = uGLUtilities::OGLfloat(blue);
		}

		void setAlpha(float alpha)
		{
			m_alpha = uGLUtilities::OGLfloat(alpha);
		}

		void setColor(float red, float green, float blue, float alpha = 1.0f)
		{
			setRed(red);
			setGreen(green);
			setBlue(blue);
			setAlpha(alpha);
		}

		float red() const { return m_red; }
		float green() const { return m_green; }
		float blue() const { return m_blue; }
		float alpha() const { return m_alpha; }

		friend bool operator==(const Color4f& lhs, const Color4f& rhs)
		{
			return (lhs.m_red == rhs.m_red) && (lhs.m_green == rhs.m_green) && (lhs.m_blue == rhs.m_blue) && (lhs.m_alpha == rhs.m_alpha);
		}

		Color4f& operator=(const Color4f& rhs)
		{
			if (this != &rhs)
				setColor(rhs.m_red, rhs.m_green, rhs.m_blue, rhs.m_alpha);

			return *this;
		}

	protected:
		float m_red;
		float m_green;
		float m_blue;
		float m_alpha;
	};

}

