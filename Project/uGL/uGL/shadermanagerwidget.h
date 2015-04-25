#ifndef SHADERMANAGERWIDGET_H
#define SHADERMANAGERWIDGET_H

#include <QWidget>
#include "ui_shadermanagerwidget.h"

#include <QtOpenGL>
#include <QOpenGLFunctions_3_3_Core>

#include "shaderprogram.h"
#include "ponctuallight.h"

typedef unsigned int uint;

class ShaderManagerWidget : public QWidget
{
	Q_OBJECT

public:
	ShaderManagerWidget(QWidget *parent = 0);
	~ShaderManagerWidget();

	void setOpenGlContext(QOpenGLFunctions_3_3_Core* oglContext);
	Shaders::ShaderProgram* addShaderProgram(const std::string& name, 
		const std::string& vertexShaderPath, 
		const std::string& fragShaderPath,
		const std::string& geoShaderPath);

	uint useShaderProgram() 
	{
		if (!context) { throw std::exception("No context loaded!"); }

		Shaders::ShaderProgram* current = programs[ui.fragmentShaderChoice->currentIndex()];

		uint programId = current->getProgramId();
		current->use();
		shaderProgramChanged = false;

		return programId;
	}

private:
	Ui::ShaderManagerWidget ui;

	QOpenGLFunctions_3_3_Core* context;

	std::vector<Shaders::ShaderProgram*> programs;

	Shaders::PonctualLight* ponctualLight;

	bool shaderProgramChanged;

private:
	void showShaderErrorMessage(const std::string& shaderName, const std::string& message);

private slots:
	void changeShaderProgram();

	void changePonctualLight();
};

#endif // SHADERMANAGERWIDGET_H
