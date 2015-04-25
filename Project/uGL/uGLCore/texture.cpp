#include "texture.h"
#include "sceneobject.h"

using namespace Textures;

Texture::Texture(QOpenGLFunctions_3_3_Core* newQOpenGlFunctions)
{
	ogl = newQOpenGlFunctions;
	textureInitialized = false;
}

Texture::~Texture()
{
	cleanTexture(textureId);
}

GLuint Texture::getTextureId() const
{
	if (!textureInitialized) { throw std::runtime_error("No texture information set!"); }
	return textureId;
}

/*
 * Load the texture in the shader if supported
 */
bool Texture::useTexture(GLuint shaderProgramId)
{
	if (textureInitialized) { 
		ogl->glBindTexture(GL_TEXTURE_2D, textureId);
		return true;
	}
	else {
		return false;
	}
}

/*
 * Importing an image to this texture.
 * If an old texture was present, it will flush it from the GPU memory
 */
void Texture::importImageAsTexture(const std::string& path, GLenum minFilter, GLenum magFilter)
{
	GLuint oldTextureId = textureId;
	if (!validateFilters(minFilter, magFilter)) { throw std::invalid_argument("Min and mag filters have non-valid values"); }

	fipImage textureImage = fipImage();
	if (!textureImage.load(path.c_str())) { throw std::invalid_argument("Path cannot be loaded as texture "+ path); }

	textureImage.convertTo32Bits(); // Standard format
	GLubyte* imagePixels = textureImage.accessPixels();

	ogl->glGenTextures(1, &textureId);
	ogl->glBindTexture(GL_TEXTURE_2D, textureId);
	ogl->glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGBA,
		textureImage.getWidth(), textureImage.getHeight(),
		0, GL_BGRA, // FreeImage loads for DirectX by default
		GL_UNSIGNED_BYTE, imagePixels);

	// Parameters for the texture
	ogl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	ogl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	ogl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	ogl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	ogl->glGenerateMipmap(GL_TEXTURE_2D);

	// Memory optimization to avoid leaks
	handleOpenGLErrors(oldTextureId);
	cleanTexture(oldTextureId);

	textureInitialized = true;
}

void Texture::cleanTexture(GLuint textureId)
{
	if (!textureInitialized) { return; }
	ogl->glDeleteTextures(1, &textureId);
}

void Texture::handleOpenGLErrors(GLuint rollbackTextureId)
{
	std::string errorText;
	GLenum glError = glGetError();

	if (glError)
	{
		switch (glError)
		{
		case GL_INVALID_ENUM:
			errorText = "Invalid enum.";
			break;

		case GL_INVALID_VALUE:
			errorText = "Invalid value.";
			break;

		case GL_INVALID_OPERATION:
			errorText = "Invalid operation.";

		default:
			errorText = "Unrecognised GLenum.";
			break;
		}
		
		textureId = rollbackTextureId;
		throw std::runtime_error("Cannot import texture in OpenGL [" + errorText + "], rolling back to the old texture if there was.");
	}
}

bool Texture::validateFilters(GLenum minFilter, GLenum magFilter)
{
	return 
		(minFilter & (GL_NEAREST | GL_LINEAR | GL_NEAREST_MIPMAP_NEAREST | GL_LINEAR_MIPMAP_NEAREST | GL_NEAREST_MIPMAP_LINEAR | GL_LINEAR_MIPMAP_LINEAR)) 
		&&
		(magFilter & (GL_NEAREST | GL_LINEAR));
}