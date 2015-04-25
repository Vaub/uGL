#pragma once

#include <QtGui\QOpenGLFunctions_3_3_Core>

#include "texture.h"

namespace Textures {

	class Terrains
	{
	public:

		Terrains(QOpenGLFunctions_3_3_Core* openGLFunctions)
			: ogl(openGLFunctions)
		{
			water = new Textures::Texture(openGLFunctions);
			water->importImageAsTexture(WATER_PATH);

			grass = new Textures::Texture(openGLFunctions);
			grass->importImageAsTexture(GRASS_PATH);

			rock = new Textures::Texture(openGLFunctions);
			rock->importImageAsTexture(ROCK_PATH);
		}

		~Terrains()
		{
			if (water) { delete water; }
			if (grass) { delete grass; }
			if (rock) { delete rock; }
		}

		Textures::Texture* getWater() const { return water; }
		Textures::Texture* getGrass() const { return grass; }
		Textures::Texture* getRock() const { return rock; }

	private:
		QOpenGLFunctions_3_3_Core* ogl;

		const std::string WATER_PATH = "images/Textures/water.jpg";
		const std::string GRASS_PATH = "images/Textures/grass.jpg";
		const std::string ROCK_PATH = "images/Textures/rock.jpg";

		Textures::Texture* water = 0;
		Textures::Texture* grass = 0;
		Textures::Texture* rock = 0;
	};

}

