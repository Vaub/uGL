#pragma once

#include "sceneobject.h"
#include "shape.h"

class SceneObjectFactory
{
public:
	static Shapes::SceneObject* cube(const glm::vec4& color = glm::vec4(1, 1, 1, 1)) {
		std::vector<Utilities::Vertex> vertices;
		std::vector<uint> indices;

		float x = 0.5f, y = 0.5f, z = 0.5f;
		using namespace Utilities;

		vertices = {
			Vertex{ glm::vec3(-x, +y, +z), color },
			Vertex{ glm::vec3(+x, +y, +z), color },
			Vertex{ glm::vec3(+x, -y, +z), color },
			Vertex{ glm::vec3(-x, -y, +z), color },
			Vertex{ glm::vec3(-x, +y, -z), color },
			Vertex{ glm::vec3(+x, +y, -z), color },
			Vertex{ glm::vec3(+x, -y, -z), color },
			Vertex{ glm::vec3(-x, -y, -z), color }
		};

		indices = {
			0, 3, 2,
			0, 2, 1,
			3, 7, 6,
			3, 6, 2,
			7, 4, 5,
			7, 5, 6,
			4, 0, 1,
			4, 1, 5,
			2, 6, 5,
			2, 5, 1,
			0, 4, 7,
			0, 7, 3
		};

		Shapes::SceneObject* cube = new Shapes::Shape(vertices, indices, true);
		cube->changeName("Cube");

		return cube;
	}

	static Shapes::SceneObject* terrain() {
		const glm::vec4 color = glm::vec4(1, 1, 1, 1);
		std::vector<Utilities::Vertex> vertices;
		std::vector<uint> indices;
		using namespace Utilities;

		vertices = {
			Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), color, glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, //Bottom left
			Vertex{ glm::vec3(-0.5f, 0.5f, 0.0f), color, glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, //Top Left
			Vertex{ glm::vec3(0.5f, 0.5f, 0.0f), color, glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, //Top right
			Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), color, glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }	//Bottom right		
		};

		indices = {
			0, 1, 2,
			0, 2, 3
		};

		Shapes::SceneObject* terrain = new Shapes::Shape(vertices, indices, false);
		terrain->changeName("Terrain");

		return terrain;
	}

	static Shapes::SceneObject* cubemap() {
		std::vector<Utilities::Vertex> vertices;
		std::vector<uint> indices;

		glm::vec4 color = glm::vec4(1, 1, 1, 1);

		float x = 1.0f, y = 1.0f, z = 1.0f;
		using namespace Utilities;

		vertices = {
			Vertex{ glm::vec3(-x, +y, -z), color },
			Vertex{ glm::vec3(-x, -y, -z), color },
			Vertex{ glm::vec3(+x, -y, -z), color },
			Vertex{ glm::vec3(+x, +y, +z), color },
			Vertex{ glm::vec3(-x, -y, +z), color },
			Vertex{ glm::vec3(-x, +y, +z), color },
			Vertex{ glm::vec3(+x, -y, +z), color },
			Vertex{ glm::vec3(+x, +y, -z), color }
		};

		indices = {
			0, 1, 2, 2, 3, 0,
			4, 1, 0, 0, 5, 4,
			2, 6, 3, 3, 7, 2,
			4, 5, 3, 3, 6, 4,
			0, 7, 3, 3, 5, 0,
			1, 4, 2, 2, 4, 6
		};

		Shapes::SceneObject* cube = new Shapes::Shape(vertices, indices, true);
		cube->changeName("Cubemap");

		return cube;
	}

private:

};

