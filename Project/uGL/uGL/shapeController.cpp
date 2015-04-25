#include "ShapeController.h"

#include <QMessageBox>
#include <iostream>
#include <glm.hpp>
#include "triangle.h"
#include "circle.h"
#include "polygon.h"
#include "water.h"
#include "bezier.h"
#include "bezierSurface.h"

#include "importmodeldialog.h"

#include "importshapemodel.h"
#include "beziercurvecreation.h"
#include "beziersurfacecreation.h"

#include "sceneobjectfactory.h"

using namespace std;

ShapeController::ShapeController(ObjectsRepository* repository, QOpenGLFunctions_3_3_Core* openGLFunctions)
	: objectsRepository(repository), ogl(openGLFunctions)
{
}

ShapeController::~ShapeController()
{
}

void ShapeController::createDefaultCube()
{
	Shapes::Cube* cube = new Shapes::Cube();
	objectsRepository->addShape(cube);

	emit shapeDataObjectAddedToRepository(cube);
}

void ShapeController::createDefaultPyramid()
{
	int sides = QInputDialog::getInt(0, "Number of sides", "Number of sides for the polygon",
		3,
		3,
		500);

	Shapes::Pyramid* pyramid = new Shapes::Pyramid(sides);
	objectsRepository->addShape(pyramid);

	emit shapeDataObjectAddedToRepository(pyramid);
}
void ShapeController::createDefaultCircle()
{
	Shapes::Circle* circle = new Shapes::Circle();
	objectsRepository->addShape(circle);

	emit shapeDataObjectAddedToRepository(circle);
}


void ShapeController::createDefaultSquare()
{
	Shapes::Polygon* square = new Shapes::Polygon(4);
	objectsRepository->addShape(square);

	emit shapeDataObjectAddedToRepository(square);
}


void ShapeController::createDefaultPolygon()
{
	int sides = QInputDialog::getInt(0, "Number of sides",
						"Number of sides for the polygon",
						3, 3, 500);

	Shapes::Polygon* polygon = new Shapes::Polygon(sides, 1);
	polygon->changeTexture(getTerrains()->getWater());
	objectsRepository->addShape(polygon);

	emit shapeDataObjectAddedToRepository(polygon);
}


void ShapeController::createDefaultTriangle()
{
	Shapes::Triangle* triangle = new Shapes::Triangle();

	objectsRepository->addShape(triangle);
	emit shapeDataObjectAddedToRepository(triangle);
}

void ShapeController::createDefaultWater()
{
	Shapes::SceneObject* water = SceneObjectFactory::terrain();
	water->changeName("Water");
	water->changeTexture(getTerrains()->getWater());
	objectsRepository->addShape(water);
	emit shapeDataObjectAddedToRepository(water);
}

void ShapeController::createDefaultGrass()
{
	Shapes::SceneObject* grass = SceneObjectFactory::terrain();
	grass->changeName("Grass");
	grass->changeTexture(getTerrains()->getGrass());
	objectsRepository->addShape(grass);
	emit shapeDataObjectAddedToRepository(grass);
}

void ShapeController::createDefaultRock()
{
	Shapes::Shape* rock = importADefaultObject("Objects/rock.obj");
	rock->changeTexture(getTerrains()->getRock());
	rock->changeName("Rock");
	objectsRepository->addShape(rock);
	emit shapeDataObjectAddedToRepository(rock);
}

void ShapeController::createBezierCurve()
{
	BezierCurveCreation* bezierCurveDialog = new BezierCurveCreation();
	if (bezierCurveDialog->exec() == QDialog::Accepted)
	{
		vector<glm::vec3> list = bezierCurveDialog->getPointList();

		if (list.size() < 2) //Vérifier qu'il y a au moins 2 points dans la courbe
		{
			QMessageBox::warning(NULL, "Error!", "Need at least 2 points!");
		}
		else
		{
			Shapes::Bezier* bezier = new Shapes::Bezier(list);
			bezier->modifyLineWidth(bezierCurveDialog->getLineWidth());

			objectsRepository->addShape(bezier);
			emit shapeDataObjectAddedToRepository(bezier);
		}
	}
	bezierCurveDialog->close();
}

void ShapeController::createBezierSurface()
{
	BezierSurfaceCreation* bezierSurfaceDialog = new BezierSurfaceCreation();
	if (bezierSurfaceDialog->exec() == QDialog::Accepted)
	{
		if (bezierSurfaceDialog->getNumberOfCurve() < 2)
		{
			QMessageBox::warning(NULL, "Error!", "Need at least 2 curves!");
		}
		else
		{
			vector<glm::vec3>* points = bezierSurfaceDialog->getPointList();
			int numberOfControlPoints = bezierSurfaceDialog->getNumberOfControlPoints();
			int numberOfRows = bezierSurfaceDialog->getNumberOfRow();
			int numberOfColumn = bezierSurfaceDialog->getNumberOfColumn();

			Shapes::BezierSurface* bezierSurface = new Shapes::BezierSurface(*points,
				numberOfControlPoints,
				numberOfColumn,
				numberOfRows);

			objectsRepository->addShape(bezierSurface);
			emit shapeDataObjectAddedToRepository(bezierSurface);
		}
	}
	bezierSurfaceDialog->close();
}

void ShapeController::importAShape()
{
	Shapes::Shape* shape = 0;

	try
	{
		ImportModelDialog* modelImporter = new ImportModelDialog();
		modelImporter->exec();

		if (!modelImporter->isModelLoaded()) { return; }

		shape = ImportShapeModel(modelImporter->getModelPath()).getModel();
		try
		{
			Textures::Texture* modelTex = new Textures::Texture(ogl);
			modelTex->importImageAsTexture(modelImporter->getTexturePath());

			shape->changeTexture(modelTex);
		}
		catch (...) { QMessageBox::information(0, "Error", "Unable to import texture!"); }
	}
	catch (...) { QMessageBox::information(0, "File invalid", "The model you tried to parse was invalid!"); }

	if (shape != nullptr)
	{
		objectsRepository->addShape(shape);
		emit shapeDataObjectAddedToRepository(shape);
	}
}

Shapes::Shape* ShapeController::importADefaultObject(std::string pathToObject)
{
	Shapes::Shape* shape = 0;
	try
	{
		shape = ImportShapeModel(pathToObject).getModel();
	}
	catch (...) { QMessageBox::information(0, "File invalid", "The model you tried to parse was invalid!"); }
	
	if (shape != nullptr)
	{
		return shape;
	}
	else
	{
		QMessageBox::information(0, "Import error", "The object you tried to import is empty");
	}
}
