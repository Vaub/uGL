#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	perspectiveCamera = new Camera::PerspectiveCamera();
	orthogonalCamera = new Camera::OrthogonalCamera();

	changeCameraType();

	this->cameraPersDefaults();
	this->orthoCameraDefaults();

	connect(ui.cameraTypeChoice, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCameraType()));

	//connect(ui.zoomXValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(cameraCommonSettingsChanged()));
	connect(ui.zoomYValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(cameraCommonSettingsChanged()));
	connect(ui.nearFieldValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(cameraCommonSettingsChanged()));
	connect(ui.farFieldValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(cameraCommonSettingsChanged()));

	connect(ui.persp_vfovDial, SIGNAL(valueChanged(int)), this, SLOT(cameraPersSettingsChanged()));
	
	connect(ui.ortho_leftValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(orthoCameraSettingsChanged()));
	connect(ui.ortho_rightValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(orthoCameraSettingsChanged()));
	connect(ui.ortho_bottomValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(orthoCameraSettingsChanged()));
	connect(ui.ortho_topValueSpinner, SIGNAL(valueChanged(double)), this, SLOT(orthoCameraSettingsChanged()));
}

CameraWidget::~CameraWidget()
{
	delete perspectiveCamera;
	delete orthogonalCamera;

	currentCamera = 0; // Just to be sure it won't be referenced
}

void CameraWidget::changeCameraType()
{
	if (ui.cameraTypeChoice->currentIndex() == 0)
	{
		currentCamera = perspectiveCamera;
		updatePerspectiveCameraUiValues();
	}
	else if (ui.cameraTypeChoice->currentIndex() == 1)
	{
		currentCamera = orthogonalCamera;
		updateOrthographicCameraUiValues();
	}

	emit cameraChanged(currentCamera);
}

void CameraWidget::cameraCommonSettingsChanged()
{
	try
	{
		currentCamera->changeZoomFactor(glm::vec2(1.0f, ui.zoomYValueSpinner->value()));
		currentCamera->changeFarAndNearField(ui.nearFieldValueSpinner->value(), ui.farFieldValueSpinner->value());
	}
	catch (...) {}

	this->updateCommonCameraUiValues();
}

void CameraWidget::cameraPersSettingsChanged()
{
	try
	{
		perspectiveCamera->changeFieldOfView(glm::radians((float)ui.persp_vfovDial->value()));
	}
	catch (...) {}

	this->updatePerspectiveCameraUiValues();
	this->cameraCommonSettingsChanged();
}

void CameraWidget::cameraPersDefaults()
{
	ui.persp_vfovDial->setValue(Camera::PerspectiveCamera::FOV_DEFAULT);
	ui.nearFieldValueSpinner->setValue(0.1f);
	ui.farFieldValueSpinner->setValue(100.0f);
}

void CameraWidget::updateCommonCameraUiValues()
{
	bool zNearState = ui.nearFieldValueSpinner->blockSignals(true);
	bool zFarState = ui.farFieldValueSpinner->blockSignals(true);
	//bool zoomXState = ui.zoomXValueSpinner->blockSignals(true);
	bool zoomYState = ui.zoomYValueSpinner->blockSignals(true);

	glm::vec2 zoom = currentCamera->getZoom();
	//ui.zoomXValueSpinner->setValue(zoom.x);
	ui.zoomYValueSpinner->setValue(zoom.y);

	ui.nearFieldValueSpinner->setValue(currentCamera->getNearField());
	ui.farFieldValueSpinner->setValue(currentCamera->getFarField());

	ui.nearFieldValueSpinner->blockSignals(zNearState);
	ui.farFieldValueSpinner->blockSignals(zFarState);
	//ui.zoomXValueSpinner->blockSignals(zoomXState);
	ui.zoomYValueSpinner->blockSignals(zoomYState);
}

void CameraWidget::updatePerspectiveCameraUiValues()
{
	bool dialState = ui.persp_vfovDial->blockSignals(true);
	ui.persp_vfovDial->setValue(glm::degrees(perspectiveCamera->getVerticalFieldOfView()));
	ui.persp_vfovDial->blockSignals(dialState);

	updateCommonCameraUiValues();
}

void CameraWidget::orthoCameraSettingsChanged()
{
	orthogonalCamera->setParameters(ui.ortho_leftValueSpinner->value(), ui.ortho_rightValueSpinner->value(),
		ui.ortho_bottomValueSpinner->value(), ui.ortho_topValueSpinner->value());

	this->cameraCommonSettingsChanged();
}

void CameraWidget::orthoCameraDefaults()
{
	orthogonalCamera->setDefaults();
	this->updateOrthographicCameraUiValues();
}

void CameraWidget::updateOrthographicCameraUiValues()
{
	bool leftState = ui.ortho_leftValueSpinner->blockSignals(true);
	bool rightState = ui.ortho_rightValueSpinner->blockSignals(true);
	bool bottomState = ui.ortho_bottomValueSpinner->blockSignals(true);
	bool topState = ui.ortho_topValueSpinner->blockSignals(true);

	ui.ortho_leftValueSpinner->setValue(orthogonalCamera->getLeft());
	ui.ortho_rightValueSpinner->setValue(orthogonalCamera->getRight());
	ui.ortho_bottomValueSpinner->setValue(orthogonalCamera->getBottom());
	ui.ortho_topValueSpinner->setValue(orthogonalCamera->getTop());

	ui.ortho_leftValueSpinner->blockSignals(leftState);
	ui.ortho_rightValueSpinner->blockSignals(rightState);
	ui.ortho_bottomValueSpinner->blockSignals(bottomState);
	ui.ortho_topValueSpinner->blockSignals(topState);

	updateCommonCameraUiValues();
}
