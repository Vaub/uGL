#pragma once

#include <QOpenGLWidget>
#include <QtOpenGL>

#include <vector>
#include <string>
#include <mutex>

#include <QOpenGLFunctions_3_3_Core>

#include "shape.h"
#include "grid.h"
#include "sceneobject.h"
#include "cubemap.h"
#include "skybox.h"

#include "genericcamera.h"
#include "cameratransformationtrategy.h"

#include "objectsRepo.h"

#include "shadermanagerwidget.h"

class uGLSceneWidget :
	public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{

	Q_OBJECT

public:
	uGLSceneWidget(QWidget* parent = 0);

	~uGLSceneWidget();

	Camera::GenericCamera* currentCamera() const { return camera; }


	void changeCameraTransformation(CameraTransformationStrategy* strategy);

	void changeShaderManager(ShaderManagerWidget* shaders);
	void changeRepository(ObjectsRepository* repository);

	void addShape(Shapes::SceneObject* shape)
	{
		//m_shapes.push_back(shape);
		needToReallocate = true;
	}

	void keyboardControlEvent(QKeyEvent* keyEvent);
	void changeSkyboxTexture(Textures::Cubemap* texture);

public slots:
	void changeCamera(Camera::GenericCamera* camera);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	virtual void mouseMoveEvent(QMouseEvent* mouseEvent);
	virtual void mousePressEvent(QMouseEvent* mouseEvent);
	virtual void mouseReleaseEvent(QMouseEvent* mouseEvent);

	virtual void wheelEvent(QWheelEvent* wheelEvent);



private:
	void translateCamera();

	void allocateGraphics();
	void renderShapes();

private:
	ObjectsRepository* repository;
	Shapes::Grid* gridXY;
	Shapes::Skybox* skybox;



	Shaders::ShaderProgram* skyboxShader;

	bool needToReallocate;
	std::mutex rendering_lock;

	ShaderManagerWidget* shaders;

	Camera::GenericCamera* camera;
	CameraTransformationStrategy* cameraTransformation;
	CameraTransformationStrategy* cameraRotationTransformation;

	glm::vec3 cameraPosition;
	bool cameraChanging;
	bool rotateMouseMovement;

	float cameraSpeedFactor;

	GLuint vertexBufferId;
	GLuint indicesBufferId;
	std::vector<GLuint> vertexArrayObjectIds;

	void loadLight(GLuint programId);
	void allocateVBOs(int vertexMemory, int indicesMemory, std::vector<Shapes::SceneObject*> shapesToRender);
	void allocateVAOs(std::vector<Shapes::SceneObject*> shapesToRender);


private slots:
	void updateGraphicsBuffer(bool deleteBuffers = false);

public slots:
	void saveAsPNG();
};
