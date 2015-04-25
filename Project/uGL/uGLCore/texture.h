#pragma once
#include <QtGui\QOpenGLFunctions_3_3_Core>
#include <string>
#include <iostream>
#include <fstream>
#include "FreeImagePlus.h"

namespace Textures {

	class Texture
	{
	protected:
		int imageWidth;
		int imageHeight;
		int imageComponent;
		int imagePixelCount;
		int imageByteSize;

		GLuint textureId;
		bool textureInitialized;

		QOpenGLFunctions_3_3_Core* ogl;
		void cleanTexture(GLuint textureId);
		void handleOpenGLErrors(GLuint rollbackTextureId);

		static bool validateFilters(GLenum minFilter, GLenum magFilter);

	public:
		Texture(QOpenGLFunctions_3_3_Core* qOpenGlFunctions);
		~Texture();

		GLuint getTextureId() const;

		virtual bool useTexture(GLuint shaderProgramId);
		void importImageAsTexture(const std::string& path,
			GLenum minFilter = GL_LINEAR,
			GLenum magFilter = GL_LINEAR);
	};

}

