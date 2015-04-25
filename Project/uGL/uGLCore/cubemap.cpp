#include "cubemap.h"

namespace Textures
{
	Cubemap::Cubemap(QOpenGLFunctions_3_3_Core* qOpenGlFunctions)
		:Texture(qOpenGlFunctions)
	{
		ogl->glGenTextures(1, &textureId);
		ogl->glActiveTexture(GL_TEXTURE0);
	}


	Cubemap::~Cubemap()
	{
	}

	void Cubemap::importImageAsTexture(const std::string& path, GLenum minFilter, GLenum magFilter)
	{
		if (side >= 6)
		{
			throw std::runtime_error("Cubemap already built!");
		}
		if (!validateFilters(minFilter, magFilter)) { throw std::invalid_argument("Min and mag filters have non-valid values"); }

		fipImage textureImage = fipImage();
		if (!textureImage.load(path.c_str())) { throw std::invalid_argument("Path cannot be loaded as texture " + path); }
		if (textureImage.getWidth() != textureImage.getHeight()) { throw std::invalid_argument("Picture must be a square!"); }

		textureImage.convertTo32Bits(); // Standard format
		GLubyte* imagePixels = textureImage.accessPixels();

		ogl->glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

		ogl->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side,
			0, GL_RGBA,
			textureImage.getWidth(), textureImage.getHeight(),
			0, GL_BGRA, // FreeImage loads for DirectX by default
			GL_UNSIGNED_BYTE, imagePixels);

		// Parameters for the texture
		ogl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
		ogl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);
		ogl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		ogl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		ogl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		side++;
		textureInitialized = true;

	}

	bool Cubemap::useTexture(GLuint shaderProgramId)
	{
		if (textureInitialized) {
			ogl->glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
			return true;
		}
		else {
			return false;
		}
	}

}
