#include "shadermanagerwidget.h"

#include <fstream>
#include <string>
#include <exception>

#include "light.h"
#include "directionnallight.h"
#include "spotlight.h"
#include "lightattenuation.h"
#include "lightcolor.h"

ShaderManagerWidget::ShaderManagerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ponctualLight = new Shaders::PonctualLight {
		glm::vec3(20.0f, 20.0f, -20.0f),
		Shaders::LightColor{
			glm::vec3(0.65f, 0.6f, 0.5f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		}
	};

	ui.directionPonctualLight->changeVector(ponctualLight->position);

	Shaders::LightColor color = ponctualLight->lightColor;
	ui.ambientPonctualLight->changeColor(glm::vec4(color.ambient, 1));
	ui.diffusePonctualLight->changeColor(glm::vec4(color.diffuse, 1));
	ui.specularPonctualLight->changeColor(glm::vec4(color.specular, 1));

	shaderProgramChanged = false;
	connect(ui.fragmentShaderChoice, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShaderProgram()));

	connect(ui.ambientPonctualLight, SIGNAL(colorChanged(const QColor&)), this, SLOT(changePonctualLight()));
	connect(ui.diffusePonctualLight, SIGNAL(colorChanged(const QColor&)), this, SLOT(changePonctualLight()));
	connect(ui.specularPonctualLight, SIGNAL(colorChanged(const QColor&)), this, SLOT(changePonctualLight()));
	connect(ui.directionPonctualLight, SIGNAL(vectorChanged()), this, SLOT(changePonctualLight()));
}

ShaderManagerWidget::~ShaderManagerWidget()
{
	while (!programs.empty()) {
		Shaders::ShaderProgram* program = programs.back();
		programs.pop_back();

		delete program;
	}
}

void ShaderManagerWidget::setOpenGlContext(QOpenGLFunctions_3_3_Core* oglContext)
{
	context = oglContext;

	addShaderProgram("Default", "./Shaders/StandardVertexShader.glsl", "./Shaders/FragmentShader.glsl", "");
	addShaderProgram("Basic light", "./Shaders/StandardVertexShader.glsl", "./Shaders/FragmentShaderLightOff.glsl", "");

	Shaders::ShaderProgram* ponctualShader = addShaderProgram("Ponctual light", "./Shaders/StandardVertexShader.glsl", "./Shaders/PonctualPhongFragmentShader.glsl", "");
	if (ponctualShader) {
		ponctualShader->addLight(ponctualLight);
	}

	Shaders::ShaderProgram* allLight = addShaderProgram("All lights", "./Shaders/StandardVertexShader.glsl", "./Shaders/LightspotFragmentShader.glsl", "");

	if (allLight) {
		Shaders::LightColor redLight = Shaders::LightColor::red();
		Shaders::LightColor greenLight = Shaders::LightColor::green();

		Shaders::LightColor normalLight = Shaders::LightColor{
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.2f, 0.2f, 0.2f),
			glm::vec3(0.3f, 0.3f, 0.3f)
		};

		Shaders::LightAttenuation attenuation50 = Shaders::LightAttenuation::fifthy();
		Shaders::LightAttenuation attenuation7 = Shaders::LightAttenuation::seven();

		Shaders::DirectionnalLight* dirLight = new Shaders::DirectionnalLight(glm::vec3(-0.5f, -0.5f, -0.5f), normalLight, "dirLight");
		Shaders::Spotlight* sp1 = new Shaders::Spotlight(glm::vec3(0, 0, -10.0f), glm::vec3(0, 0, 1.0f), 2, 5, attenuation50, greenLight, "spotlights[0]");
		Shaders::Spotlight* sp2 = new Shaders::Spotlight(glm::vec3(0, 0, 10.0f), glm::vec3(0, 0, -1.0f), 2, 5, attenuation50, redLight, "spotlights[1]");
		Shaders::Spotlight* sp3 = new Shaders::Spotlight(glm::vec3(0, 20.0f, 0), glm::vec3(0, -1.0f, 0), 10, 20, attenuation50, Shaders::LightColor::purple(), "spotlights[2]");

		allLight->addLight(dirLight);
		allLight->addLight(sp1);
		allLight->addLight(sp2);
		allLight->addLight(sp3);
	}

	addShaderProgram("Normal debugging", "./Shaders/NormalsVertexShader.glsl", "./Shaders/NormalsFragmentShader.glsl", "./Shaders/NormalsGeometricShader.glsl");

	

	this->shaderProgramChanged = true;
	ui.fragmentShaderChoice->setCurrentIndex(0);
}

Shaders::ShaderProgram* ShaderManagerWidget::addShaderProgram(const std::string& name,
	const std::string& vertexShaderPath,
	const std::string& fragShaderPath,
	const std::string& geoShaderPath) {
	Shaders::ShaderProgram* program = 0;
	
	try {
		program = new Shaders::ShaderProgram(context, name, vertexShaderPath, fragShaderPath, geoShaderPath);

		programs.push_back(program);
		ui.fragmentShaderChoice->addItem(name.c_str());

		shaderProgramChanged = true;
	}
	catch (std::exception& e) { showShaderErrorMessage(name, e.what()); }

	return program;
}

void ShaderManagerWidget::showShaderErrorMessage(const std::string& shaderName, const std::string& message)
{
	QString errorTitle(("Error loading shader " + shaderName).c_str());
	QString errorMessage(message.c_str());

	QMessageBox* error = new QMessageBox(0);
	error->setText(errorMessage);
	error->setWindowTitle(errorTitle);
	error->setModal(true);
	error->show();
}

void ShaderManagerWidget::changeShaderProgram() {
	ui.fragmentShaderChoice->currentIndex();
	this->shaderProgramChanged = true;
}

void ShaderManagerWidget::changePonctualLight() {
	ponctualLight->position = ui.directionPonctualLight->getVector();
	ponctualLight->lightColor = Shaders::LightColor{
		glm::vec3(ui.ambientPonctualLight->getCurrentColorF()),
		glm::vec3(ui.diffusePonctualLight->getCurrentColorF()),
		glm::vec3(ui.specularPonctualLight->getCurrentColorF())
	};
}