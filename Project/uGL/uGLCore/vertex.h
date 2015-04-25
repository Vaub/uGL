#pragma once


#include <glm.hpp>

typedef glm::vec3 Position;
typedef glm::vec4 Color;
typedef glm::vec2 TextureCoordinates;
typedef glm::vec3 Normal;

namespace Utilities
{

	struct Vertex
	{
		static const int VERTEX_SIZE = 12;

		Vertex()
		{
			position = Position(0.0f, 0.0f, 0.0f);
			color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			textureCoordinates = TextureCoordinates(0.0f, 0.0f);
			normal = Normal(0.0f, 0.0f, 0.0f);
		}

		Vertex(Position position, 
			Color color, 
			TextureCoordinates textureCoordinates = TextureCoordinates(0.0f, 0.0f),
			Normal normal = Normal(0.0f, 0.0f, 0.0f))
			: position(position), color(color), textureCoordinates(textureCoordinates), normal(normal)
		{
		}

		Position position;
		Color color;
		TextureCoordinates textureCoordinates;
		Normal normal;


		float operator[](int index)
		{
			float vertexFloat;

			vertexFloat = (index < 3) ? position[index] :
						  (index < 7) ? color[index - 3] :
						  (index < 9) ? textureCoordinates[index - 7] :
						  (index < 12) ? normal[index - 9] :
						  throw new std::invalid_argument("Out of bound exception!");

			return vertexFloat;
		}
	};

}
