#ifndef UGLWINDOW_H
#define UGLWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_uglwindow.h"
#include "shapeController.h"
#include "graphSceneItem.h"
#include "orthogonalcamera.h"
#include "perspectivecamera.h"



class uGLWindow : public QMainWindow
{
	Q_OBJECT
public:
	uGLWindow( QWidget *parent = 0);
	~uGLWindow();

protected:
	virtual void keyPressEvent(QKeyEvent* keyEvent);

private:
	void initUi();

private:
	Ui::uGLWindowClass ui;

	ShapeController* shapeController;
	QActionGroup* cameraGroup;

	static float scaleFromSliderValue(uint value) {
		return (value > 0) ? (float)value / 20.0f : 0.005f;
	}

	static uint sliderValueFromScale(float value) {
		return (int)(value * 20.0f);
	}

public slots:
	void cameraActionChanged();
	void addNewRepositoryItemToGUI(Shapes::SceneObject* newShape);
	void changeShapeItemFocus(QTreeWidgetItem* item);
	void scaleFocusedShape();
	void scaleIndividualControl();
	void translateFocusedShape();
	void rotateFocusedShape();
	void renderFocusedShapeAsMesh();
	void changeFocusedShapeMaterial();
	void renameFocusedShape();
	void changeSkybox();
};

#endif // UGLWINDOW_H
