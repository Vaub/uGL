#pragma once

#include <memory>
#include "color4f.h"

namespace Utilities
{

	class Colors
	{
	public:

		static std::unique_ptr<Color4f> White() { return std::make_unique<Color4f>(1.0f, 1.0f, 1.0f); }

		static std::unique_ptr<Color4f> Red() { return std::make_unique<Color4f>(1.0f, 0, 0); }
		static std::unique_ptr<Color4f> Green() { return std::make_unique<Color4f>(0, 1.0f, 0); }
		static std::unique_ptr<Color4f> Blue() { return std::make_unique<Color4f>(0, 0, 1.0f); }

		static std::unique_ptr<Color4f> Magenta() { return std::make_unique<Color4f>(1.0f, 0, 1.0f); }
		static std::unique_ptr<Color4f> Yellow() { return std::make_unique<Color4f>(1.0f, 1.0f, 0); }
		static std::unique_ptr<Color4f> Cyan() { return std::make_unique<Color4f>(0, 1.0f, 1.0f); }
	};

}

