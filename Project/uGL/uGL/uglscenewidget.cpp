#include "uglscenewidget.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <math.h>
#include <ctime>

#include "vertex.h"
#include "material.h"
#include "terrains.h"

#include "sceneobjectfactory.h"

#include "orthogonalcamera.h"
#include "perspectivecamera.h"
#include "importshapemodel.h"
#include "rotationcameratransformationstrategy.h"

using namespace std;
using namespace Shapes;
using namespace Utilities;

uGLSceneWidget::uGLSceneWidget(QWidget* parent)
:QOpenGLWidget(parent)
{
	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	this->setMouseTracking(true);

	cameraRotationTransformation = 0;

	cameraChanging = false;
	rotateMouseMovement = false;
	needToReallocate = false;

	gridXY = new Grid(100, 100);
	//gridXY->scaleShape(0.5f);
	//gridXY->changePosition(glm::vec3(-25.0f, -25.0f, 0.0f));
	//gridXY->rotate(glm::vec3(0, 0, 90.0f));

	camera = 0;
	cameraTransformation = 0;
	repository = 0;

	cameraSpeedFactor = 2.0f;

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);
}

uGLSceneWidget::~uGLSceneWidget()
{
}

void uGLSceneWidget::changeShaderManager(ShaderManagerWidget* shaders)
{
	this->shaders = shaders;
}

void uGLSceneWidget::changeRepository(ObjectsRepository* repository)
{
	this->repository = repository;

	connect(repository, SIGNAL(repositoryChanged()), this, SLOT(updateGraphicsBuffer()));
	this->updateGraphicsBuffer(false);
}

void uGLSceneWidget::changeCamera(Camera::GenericCamera* camera)
{
	this->camera = camera;

	if (cameraRotationTransformation) delete cameraRotationTransformation;
	cameraRotationTransformation = new RotationCameraTransformationStrategy(camera);
}

void uGLSceneWidget::changeCameraTransformation(CameraTransformationStrategy* strategy)
{
	if (cameraTransformation)
		delete cameraTransformation;

	cameraTransformation = strategy;
}

void uGLSceneWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	if (!cameraChanging || !camera) return;

	float deltaX = cameraSpeedFactor * ((float)(mouseEvent->x() - cameraPosition.x) / (float)this->width());
	float deltaY = cameraSpeedFactor * ((float)(cameraPosition.y - mouseEvent->y()) / (float)this->height());

	cameraPosition.x = mouseEvent->x();
	cameraPosition.y = mouseEvent->y();

	if (rotateMouseMovement && cameraRotationTransformation)
	{
		cameraRotationTransformation->transform(glm::vec2(-deltaX, -deltaY));
	}
	else if (cameraTransformation)
	{
		cameraTransformation->transform(glm::vec2(-deltaX, -deltaY));
	}
}

void uGLSceneWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
	cameraPosition = glm::vec3(mouseEvent->x(), mouseEvent->y(), 0.0f);
	cameraChanging = true;

	rotateMouseMovement = (mouseEvent->button() == Qt::MiddleButton);
}

void uGLSceneWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	cameraChanging = false;
	rotateMouseMovement = (mouseEvent->button() == Qt::MiddleButton);
}

void uGLSceneWidget::wheelEvent(QWheelEvent* wheelEvent)
{
	if (!camera) return;

	float angleDelta = wheelEvent->delta() / 8.0f;
	camera->dolly(cameraSpeedFactor * glm::radians(angleDelta));
}

void uGLSceneWidget::keyboardControlEvent(QKeyEvent* keyEvent)
{
	glm::vec2 speed(0.0f, 0.0f);

	switch (keyEvent->key())
	{
	case Qt::Key_Up:
		speed.y = 0.1f;
		break;

	case Qt::Key_Down:
		speed.y = -0.1f;
		break;

	case Qt::Key_Left:
		speed.x = -0.1f;
		break;

	case Qt::Key_Right:
		speed.x = 0.1f;
		break;
	}

	camera->pan(speed);
}

void uGLSceneWidget::initializeGL()
{
	initializeOpenGLFunctions();
	shaders->setOpenGlContext(this);

	skyboxShader = new Shaders::ShaderProgram(this, "skyboxShader", "./Shaders/SkyboxVertexShader.glsl", "./Shaders/SkyboxFragmentShader.glsl");

	Textures::Cubemap* skyboxTexture = new Textures::Cubemap(this);
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_rt.png");
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_lf.png");
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_dn.png");
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_up.png");
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_bk.png");
	skyboxTexture->importImageAsTexture("./Skybox/corona/corona_ft.png");

	skybox = new Shapes::Skybox(skyboxShader);
	skybox->changeTexture(skyboxTexture);

	glEnable(GL_DEPTH_TEST);

	// Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	needToReallocate = true;
}

void uGLSceneWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	camera->contextUpdated(this);
}

void uGLSceneWidget::paintGL()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rendering_lock.lock();

	if (needToReallocate)
		allocateGraphics();

	rendering_lock.unlock();

	renderShapes();
}

void uGLSceneWidget::allocateGraphics()
{
	needToReallocate = false;

	// Loading the model to load in GPU memory
	std::vector<Shapes::SceneObject*> shapesToRender;

	if (repository) {
		shapesToRender = repository->listsShapesInGraph();
	}
	shapesToRender.insert(shapesToRender.begin(), skybox);
	shapesToRender.push_back(gridXY);

	// Calculating the memory needed for the buffer
	int vertexMemory = 0;
	int indicesMemory = 0;
	for (int i = 0; i < shapesToRender.size(); i++)
	{
		vertexMemory += shapesToRender[i]->getVerticesByteSize();
		indicesMemory += shapesToRender[i]->getIndicesByteSize();
	}

	allocateVBOs(vertexMemory, indicesMemory, shapesToRender);
	allocateVAOs(shapesToRender);
}

void uGLSceneWidget::renderShapes()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId); // bind the indices buffer

	// Loading shapes to render
	std::vector<Shapes::SceneObject*> shapesToRender;

	if (repository) {
		shapesToRender = repository->listsShapesInGraph();
	}
	shapesToRender.insert(shapesToRender.begin(), skybox);
	shapesToRender.push_back(gridXY);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int indicesOffset = 0;
	for (int i = 0; i < shapesToRender.size(); i++)
	{
		// Getting the VAO for the current shape
		GLuint vaoId = vertexArrayObjectIds[i];
		glBindVertexArray(vaoId);

		// Loading everything needed for the shaders
		
		if (shapesToRender[i]->isDrawnAsMesh()) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

		uint shaderProgramId = shaders->useShaderProgram();

		loadLight(shaderProgramId);
		shapesToRender[i]->render(indicesOffset, this, shaderProgramId, camera);

		if (shapesToRender[i]->isDrawnAsMesh()) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

		indicesOffset += shapesToRender[i]->getIndicesByteSize(); // Going to the next shape!
	}
}

void uGLSceneWidget::loadLight(GLuint programId) {

	//GLint lightDirLoc = glGetUniformLocation(programId, "light.position");
	//
	//glUniform3f(lightDirLoc, 0.0f, 0.0f, 20.0f);
	//
	//glUniform3f(glGetUniformLocation(programId, "light.ambient"), 0.65f, 0.6f, 0.5f);
	//glUniform3f(glGetUniformLocation(programId, "light.diffuse"), 0.8f, 0.8f, 0.8f);
	//glUniform3f(glGetUniformLocation(programId, "light.specular"), 1.0f, 1.0f, 1.0f);
}

void uGLSceneWidget::updateGraphicsBuffer(bool deleteBuffers)
{
	rendering_lock.lock();

	needToReallocate = true;

	if (deleteBuffers)
	{
		glDeleteFramebuffers(1, &vertexBufferId);
		glDeleteFramebuffers(1, &indicesBufferId);
		glDeleteVertexArrays(vertexArrayObjectIds.size(), &vertexArrayObjectIds[0]);
	}

	rendering_lock.unlock();
}

void uGLSceneWidget::saveAsPNG()
{
	QImage imageToExport = this->grabFramebuffer();
	std::string filename = QFileDialog::getSaveFileName(0, "Save image", "", ".png").toStdString();

	imageToExport.save(filename.c_str(), "PNG");
	return;
}

void  uGLSceneWidget::allocateVBOs(int vertexMemory, int indicesMemory, std::vector<Shapes::SceneObject*> shapesToRender)
{
	// Creating the Vertices and Indices VBOs
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexMemory, NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &indicesBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesMemory, NULL, GL_DYNAMIC_DRAW);

	int vertexOffset = 0;
	int indicesOffset = 0;
	for (int i = 0; i < shapesToRender.size(); i++) // adding shapes to the vbos
	{
		float* verticesArray = shapesToRender[i]->vertices();
		GLuint* indicesArray = shapesToRender[i]->indices();

		// vertices
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glBufferSubData(GL_ARRAY_BUFFER, vertexOffset, shapesToRender[i]->getVerticesByteSize(), verticesArray);

		// indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indicesOffset, shapesToRender[i]->getIndicesByteSize(), indicesArray);

		vertexOffset += shapesToRender[i]->getVerticesByteSize();
		indicesOffset += shapesToRender[i]->getIndicesByteSize();
	}
}

void uGLSceneWidget::allocateVAOs(std::vector<Shapes::SceneObject*> shapesToRender)
{
	// Creating the VAOs storage
	vertexArrayObjectIds = std::vector<GLuint>(shapesToRender.size());
	if (vertexArrayObjectIds.size() > 0)
		glGenVertexArrays(shapesToRender.size(), &vertexArrayObjectIds[0]);

	int vertexAttribOffset = 0;
	for (int i = 0; i < shapesToRender.size(); i++) // Creates a VAO for every object
	{
		int colorOffset = sizeof(float)* 3;
		int texOffset = sizeof(float)* 7;
		int normalOffset = sizeof(float)* 9;

		GLuint vaoId = vertexArrayObjectIds[i];

		glBindVertexArray(vaoId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		// Mapping the vertices informations to the VAO
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* Vertex::VERTEX_SIZE, (void*)(vertexAttribOffset)); // position (x,y,z)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float)* Vertex::VERTEX_SIZE, (void*)(vertexAttribOffset + colorOffset)); // color (r,g,b,a)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)* Vertex::VERTEX_SIZE, (void*)(vertexAttribOffset + texOffset)); // texCoord (u,v)
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float)* Vertex::VERTEX_SIZE, (void*)(vertexAttribOffset + normalOffset)); // normals (x,y,z)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);

		vertexAttribOffset += shapesToRender[i]->getVerticesByteSize();
	}
}

void uGLSceneWidget::changeSkyboxTexture(Textures::Cubemap* texture)
{
	skybox->changeTexture(texture);
}
