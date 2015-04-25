#include "materialwidget.h"

MaterialWidget::MaterialWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	addMaterial("White plastic", Shaders::Material::whitePlastic());
	addMaterial("White rubber", Shaders::Material::whiteRubber());
	addMaterial("Chrome", Shaders::Material::chrome());
	addMaterial("Brass", Shaders::Material::brass());
	addMaterial("Bronze", Shaders::Material::bronze());
	addMaterial("Ruby", Shaders::Material::ruby());

	ui.materialChoice->setCurrentIndex(0);

	connect(ui.materialChoice, SIGNAL(currentIndexChanged(int)), this, SLOT(changedMaterialIndex()));
	connect(ui.addMaterial, SIGNAL(clicked()), this, SIGNAL(addMaterial()));
}

MaterialWidget::~MaterialWidget()
{

}

void MaterialWidget::addMaterial() {
	
}

void MaterialWidget::addMaterial(const std::string& name, const Shaders::Material& material) {
	materials.push_back(material);
	ui.materialChoice->addItem(name.c_str());
}

void MaterialWidget::changedMaterialIndex() {
	emit changedMaterial();
}
