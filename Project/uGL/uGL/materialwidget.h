#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QWidget>
#include "ui_materialwidget.h"

#include <vector>

#include "material.h"

class MaterialWidget : public QWidget
{
	Q_OBJECT

public:
	MaterialWidget(QWidget *parent = 0);
	~MaterialWidget();

	Shaders::Material currentMaterial() const { return materials[ui.materialChoice->currentIndex()]; };

private:
	Ui::MaterialWidget ui;

	std::vector<Shaders::Material> materials;

private slots:
	void addMaterial();
	void addMaterial(const std::string& name, const Shaders::Material& material);

	void changedMaterialIndex();

signals:
	void changedMaterial();
};

#endif // MATERIALWIDGET_H
