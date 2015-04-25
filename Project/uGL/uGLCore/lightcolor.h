#pragma once

#include <glm.hpp>

namespace Shaders
{
	struct LightColor
	{
		LightColor()
		{
		}

		LightColor(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
			: ambient(ambient), diffuse(diffuse), specular(specular)
		{
		}

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		static LightColor red() 
		{
			glm::vec3 ambient(0.3f, 0.05f, 0.0f);
			glm::vec3 diffuse(0.8f, 0.10f, 0.0f);
			glm::vec3 specular(1.0f, 0.9f, 0.75f);

			return LightColor(ambient, diffuse, specular);
		}

		static LightColor green()
		{
			glm::vec3 ambient(0.0f, 0.03f, 0.0f);
			glm::vec3 diffuse(0.10f, 0.8f, 0.10f);
			glm::vec3 specular(0.8f, 1.0f, 0.8f);

			return LightColor(ambient, diffuse, specular);
		}

		static LightColor purple()
		{
			glm::vec3 ambient(0.0f, 0.05f, 0.3f);
			glm::vec3 diffuse(0.9f, 0.10f, 0.8f);
			glm::vec3 specular(0.75f, 0.9f, 1.0f);

			return LightColor(ambient, diffuse, specular);
		}
	};
}