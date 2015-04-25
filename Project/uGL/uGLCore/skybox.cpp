#include "skybox.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace Shapes;

Skybox::Skybox(Shaders::ShaderProgram* skyboxShader)
	: skyboxShader(skyboxShader)
{
	changeName("Skybox");
}


Skybox::~Skybox()
{
}

void Skybox::render(
		int byteOffset,
		OpenGLContext* ogl,
		GLuint shaderProgramId,
		Camera::GenericCamera* camera)
{
	if (!skyboxShader) { return; }

	ogl->glDepthMask(GL_FALSE);
	
	skyboxShader->use();
	GLuint skyboxShaderId = skyboxShader->getProgramId();
	ogl->glUniform1i(ogl->glGetUniformLocation(skyboxShaderId, "skybox"), 0);

	camera->applyCamera(skyboxShaderId, ogl);
	//glm::mat4 projection = glm::perspective(camera->getZoom().y, 1920.0f / 1080.0f, 0.1f, 100.0f);
	//ogl->glUniformMatrix4fv(ogl->glGetUniformLocation(skyboxShaderId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	loadTexture(ogl, skyboxShaderId);

	ogl->glDrawElements(renderingMode, getIndicesCount(), GL_UNSIGNED_INT, (void*)byteOffset);

	ogl->glDepthMask(GL_TRUE);
}
