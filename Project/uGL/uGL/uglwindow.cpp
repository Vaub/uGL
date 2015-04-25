#include "uglwindow.h"

#include "translationcameratransformationstrategy.h"
#include "rotationcameratransformationstrategy.h"
#include "depthcameratransformationstrategy.h"
#include "rollcameratransformationstrategy.h"
#include "vertigotransformationstrategy.h"

#include "importshapemodel.h"
#include "Bezier.h"
#include "bezierSurface.h"

#include "sceneobjectfactory.h"
#include "changeskyboxdialog.h"

#include <math.h>
#include <typeinfo>

#include <glm.hpp>

uGLWindow::uGLWindow(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);

	ObjectsRepository* repo = new ObjectsRepository();
	shapeController = new ShapeController(repo, ui.openGLWidget);

	ui.openGLWidget->changeCamera(ui.cameraWidget->getCurrentCamera());
	ui.openGLWidget->changeShaderManager(ui.shaderManager);
	ui.openGLWidget->changeRepository(repo);

	this->initUi();

	connect(ui.cameraWidget, SIGNAL(cameraChanged(Camera::GenericCamera*)), ui.openGLWidget, SLOT(changeCamera(Camera::GenericCamera*)));

	connect(ui.actionCamera_Translation, SIGNAL(triggered()), this, SLOT(cameraActionChanged()));
	connect(ui.actionCameraDepth, SIGNAL(triggered()), this, SLOT(cameraActionChanged()));
	connect(ui.actionCamera_Rotation, SIGNAL(triggered()), this, SLOT(cameraActionChanged()));
	connect(ui.actionCamera_Roll, SIGNAL(triggered()), this, SLOT(cameraActionChanged()));
	connect(ui.actionVertigo, SIGNAL(triggered()), this, SLOT(cameraActionChanged()));

	connect(ui.actionImport_model, SIGNAL(triggered()), shapeController, SLOT(importAShape()));
	connect(ui.actionExport_as_PNG, SIGNAL(triggered()), ui.openGLWidget, SLOT(saveAsPNG()));

	connect(ui.actionCube, SIGNAL(triggered()), shapeController, SLOT(createDefaultCube()));
	connect(ui.actionPyramid, SIGNAL(triggered()), shapeController, SLOT(createDefaultPyramid()));

	connect(ui.actionCircle, SIGNAL(triggered()), shapeController, SLOT(createDefaultCircle()));
	connect(ui.actionPolygon, SIGNAL(triggered()), shapeController, SLOT(createDefaultPolygon()));
	connect(ui.actionTriangle, SIGNAL(triggered()), shapeController, SLOT(createDefaultTriangle()));
	connect(ui.actionSquare, SIGNAL(triggered()), shapeController, SLOT(createDefaultSquare()));

	connect(ui.actionWater, SIGNAL(triggered()), shapeController, SLOT(createDefaultWater()));
	connect(ui.actionGrass, SIGNAL(triggered()), shapeController, SLOT(createDefaultGrass()));
	connect(ui.action3D_rock, SIGNAL(triggered()), shapeController, SLOT(createDefaultRock()));

	connect(ui.actionBezier_curve, SIGNAL(triggered()), shapeController, SLOT(createBezierCurve()));
	connect(ui.actionBezier_surface, SIGNAL(triggered()), shapeController, SLOT(createBezierSurface()));

	connect(shapeController, SIGNAL(shapeDataObjectAddedToRepository(Shapes::SceneObject*)), this, SLOT(addNewRepositoryItemToGUI(Shapes::SceneObject*)));

	connect(ui.sceneGraph, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changeShapeItemFocus(QTreeWidgetItem*)));

	connect(ui.translateX, SIGNAL(valueChanged(double)), this, SLOT(translateFocusedShape()));
	connect(ui.translateY, SIGNAL(valueChanged(double)), this, SLOT(translateFocusedShape()));
	connect(ui.translateZ, SIGNAL(valueChanged(double)), this, SLOT(translateFocusedShape()));

	connect(ui.rotationX, SIGNAL(valueChanged(int)), this, SLOT(rotateFocusedShape()));
	connect(ui.rotationY, SIGNAL(valueChanged(int)), this, SLOT(rotateFocusedShape()));
	connect(ui.rotationZ, SIGNAL(valueChanged(int)), this, SLOT(rotateFocusedShape()));

	connect(ui.scaleX, SIGNAL(valueChanged(double)), this, SLOT(scaleFocusedShape()));
	connect(ui.scaleY, SIGNAL(valueChanged(double)), this, SLOT(scaleFocusedShape()));
	connect(ui.scaleZ, SIGNAL(valueChanged(double)), this, SLOT(scaleFocusedShape()));
	connect(ui.scaleXYZ, SIGNAL(valueChanged(int)), this, SLOT(scaleFocusedShape()));
	connect(ui.individualScaleControl, SIGNAL(stateChanged(int)), this, SLOT(scaleIndividualControl()));

	connect(ui.shapeMaterial, SIGNAL(changedMaterial()), this, SLOT(changeFocusedShapeMaterial()));

	connect(ui.renameShape, SIGNAL(clicked()), this, SLOT(renameFocusedShape()));

	connect(ui.shapeRenderAsMesh, SIGNAL(stateChanged(int)), this, SLOT(renderFocusedShapeAsMesh()));

	connect(ui.actionModify_Skybox, SIGNAL(triggered()), this, SLOT(changeSkybox()));
}

uGLWindow::~uGLWindow()
{
}

void uGLWindow::keyPressEvent(QKeyEvent* keyEvent)
{
	ui.openGLWidget->keyboardControlEvent(keyEvent);
}

void uGLWindow::initUi()
{
	cameraGroup = new QActionGroup(this);
	cameraGroup->addAction(ui.actionCamera_Translation);
	cameraGroup->addAction(ui.actionCameraDepth);
	cameraGroup->addAction(ui.actionCamera_Rotation);
	cameraGroup->addAction(ui.actionCamera_Roll);
	cameraGroup->addAction(ui.actionVertigo);
}

void uGLWindow::cameraActionChanged()
{
	Camera::GenericCamera* camera = ui.openGLWidget->currentCamera();

	if (ui.actionCamera_Translation->isChecked())
		ui.openGLWidget->changeCameraTransformation(new TranslationCameraTransformationStrategy(camera));
	else if (ui.actionCamera_Rotation->isChecked())
		ui.openGLWidget->changeCameraTransformation(new RotationCameraTransformationStrategy(camera));
	else if (ui.actionCameraDepth->isChecked())
		ui.openGLWidget->changeCameraTransformation(new DepthCameraTransformationStrategy(camera));
	else if (ui.actionCamera_Roll->isChecked())
		ui.openGLWidget->changeCameraTransformation(new RollCameraTransformationStrategy(camera));
	else if (ui.actionVertigo->isChecked())
		ui.openGLWidget->changeCameraTransformation(new VertigoTransformationStrategy(camera));
}

void uGLWindow::addNewRepositoryItemToGUI(Shapes::SceneObject* newShape)
{
	GraphSceneItem* item = new GraphSceneItem(newShape);
	ui.sceneGraph->addTopLevelItem(item);
}

void uGLWindow::changeShapeItemFocus(QTreeWidgetItem* item)
{
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(item);

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();

		glm::vec3 position = shape->currentPosition();
		ui.translateX->setValue(position.x);
		ui.translateY->setValue(position.y);
		ui.translateZ->setValue(position.z);

		glm::vec3 scale = shape->scaleFactor();
		ui.scaleX->setValue(scale.x);
		ui.scaleY->setValue(scale.y);
		ui.scaleZ->setValue(scale.z);
		ui.scaleXYZ->setValue(sliderValueFromScale(scale.x));

		//glm::vec4 color = shape->getC
		//ui.shapeColor->changeColor();

		ui.shapeRenderAsMesh->setChecked(shapeItem->getShape()->isDrawnAsMesh());
	}
}

void uGLWindow::scaleFocusedShape() {
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();

		if(ui.individualScaleControl->isChecked()) {
			glm::vec3 scale = shape->scaleFactor();
			scale.x = ui.scaleX->value();
			scale.y = ui.scaleY->value();
			scale.z = ui.scaleZ->value();

			shape->scaleShape(scale);
		}
		else {
			glm::vec3 scaleFactor = scaleFromSliderValue(ui.scaleXYZ->value()) * glm::vec3(1.0f, 1.0f, 1.0f);
			shape->scaleShape(scaleFactor);

			glm::vec3 scale = shape->scaleFactor();
			ui.scaleX->setValue(scale.x);
			ui.scaleY->setValue(scale.y);
			ui.scaleZ->setValue(scale.z);
		}
	}
}

void uGLWindow::scaleIndividualControl() {
	if (ui.individualScaleControl->isChecked()) {
		ui.scaleXYZ->setEnabled(false);

		ui.scaleX->setEnabled(true);
		ui.scaleY->setEnabled(true);
		ui.scaleZ->setEnabled(true);
	}
	else {
		ui.scaleXYZ->setEnabled(true);

		ui.scaleX->setEnabled(false);
		ui.scaleY->setEnabled(false);
		ui.scaleZ->setEnabled(false);
	}
}

void uGLWindow::translateFocusedShape()
{
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();

		shape->changePosition(glm::vec3(ui.translateX->value(), ui.translateY->value(), ui.translateZ->value()));

		glm::vec3 position = shapeItem->getShape()->currentPosition();
		ui.translateX->setValue(position.x);
		ui.translateY->setValue(position.y);
		ui.translateZ->setValue(position.z);
	}
}

void uGLWindow::rotateFocusedShape()
{
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();

		shape->rotate(glm::vec3(ui.rotationX->value(), ui.rotationY->value(), ui.rotationZ->value()));
	}
}

void uGLWindow::renderFocusedShapeAsMesh()
{
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();
		shape->setDrawAsMesh(ui.shapeRenderAsMesh->isChecked());
	}
}

void uGLWindow::changeFocusedShapeMaterial() {
	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();
		shape->changeMaterial(ui.shapeMaterial->currentMaterial());
	}
}

void uGLWindow::renameFocusedShape() {

	GraphSceneItem* shapeItem = dynamic_cast<GraphSceneItem*>(ui.sceneGraph->currentItem());

	if (shapeItem != nullptr)
	{
		Shapes::SceneObject* shape = shapeItem->getShape();

		bool ok;
		QString text = QInputDialog::getText(this,
			("Rename " + shape->getName()).c_str(),
			"New name : ",
			QLineEdit::Normal,
			shape->getName().c_str(),
			&ok);

		if (ok && !text.isEmpty()) {
			shape->changeName(text.toStdString());
			shapeItem->setText(0, text);

			ui.sceneGraph->update();
		}
	}

}

void uGLWindow::changeSkybox()
{
	ChangeSkyboxDialog* changeSkyboxDialog = new ChangeSkyboxDialog(ui.openGLWidget);
	changeSkyboxDialog->exec();
	try{
		if (changeSkyboxDialog->isPictureLoaded())
		{
			Textures::Cubemap* cubemap = changeSkyboxDialog->loadCubemap();
			ui.openGLWidget->changeSkyboxTexture(cubemap);
		}
	}
	catch (...) { QMessageBox::information(0,"Failed to load cubemap!", "A picture is not valid!"); }

}
