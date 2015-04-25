#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include "ui_camerawidget.h"

#include "genericcamera.h"
#include "orthogonalcamera.h"
#include "perspectivecamera.h"

class CameraWidget : public QWidget
{
	Q_OBJECT

public:
	CameraWidget(QWidget *parent = 0);
	~CameraWidget();

	inline Camera::GenericCamera* getCurrentCamera() const { return currentCamera; }

public slots:
	void changeCameraType();

	void cameraCommonSettingsChanged();

	void cameraPersSettingsChanged();
	void cameraPersDefaults();

	void orthoCameraSettingsChanged();
	void orthoCameraDefaults();

private:
	Ui::CameraWidget ui;

	Camera::GenericCamera* currentCamera = 0;

	Camera::OrthogonalCamera* orthogonalCamera = 0;
	Camera::PerspectiveCamera* perspectiveCamera = 0;

	void updatePerspectiveCameraUiValues();
	void updateOrthographicCameraUiValues();

	void updateCommonCameraUiValues();

signals:
	void cameraChanged(Camera::GenericCamera* camera);

};

#endif // CAMERAWIDGET_H
