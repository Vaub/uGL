#pragma once

namespace Shaders {

	struct LightAttenuation
	{
		LightAttenuation(float constant, float linear, float quadratic)
			: constant(constant), linear(linear), quadratic(quadratic)
		{
		}

		float constant;
		float linear;
		float quadratic;

		static LightAttenuation seven() { return LightAttenuation(1.0f, 0.7f, 1.8f); }
		static LightAttenuation fifthy() { return LightAttenuation(1.0f, 0.09f, 0.032f); }
		static LightAttenuation sixHundred() { return LightAttenuation(1.0f, 0.0014f, 0.0002f); }
	};

}

