#pragma once

#include "sceneobject.h"

namespace Textures
{
	class Cubemap : public Texture
	{

	public:
		Cubemap(QOpenGLFunctions_3_3_Core* qOpenGlFunctions);
		~Cubemap();

		virtual bool useTexture(GLuint shaderProgramId);
		virtual void Cubemap::importImageAsTexture(const std::string& path,
			GLenum minFilter = GL_LINEAR,
			GLenum magFilter = GL_LINEAR);


	private:
		int side = 0;
	};

}

