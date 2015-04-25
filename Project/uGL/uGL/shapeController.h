#pragma once

#include <QtGui\qopenglfunctions_3_3_core.h>

#include "qobject.h"
#include "objectsRepo.h"

#include "terrains.h"
#include "shape.h"

#include "cube.h"
#include "pyramid.h"

class ShapeController: public QObject
{
	Q_OBJECT

public:
	ShapeController(ObjectsRepository* objectsRepository, QOpenGLFunctions_3_3_Core* openGLFunctions);
	~ShapeController();

public slots:
	void createDefaultCube();
	void createDefaultCircle();
	void createDefaultSquare();
	void createDefaultPolygon();
	void createDefaultWater();
	void createDefaultGrass();
	void createDefaultRock();
	void createDefaultTriangle();
	void createDefaultPyramid();
	void createBezierCurve();
	void createBezierSurface();
	void importAShape();

signals:
	Shapes::SceneObject* shapeDataObjectAddedToRepository(Shapes::SceneObject* shapeAdded);

private:
	ObjectsRepository* objectsRepository = 0;
	QOpenGLFunctions_3_3_Core* ogl = 0;
	Textures::Terrains* terrains = 0;
	Shapes::Shape* importADefaultObject(std::string pathToObject);

	Textures::Terrains* getTerrains()
	{ 
		if (!terrains) { terrains = new Textures::Terrains(ogl); }
		return terrains;
	}
};
