#pragma once
#include <QTreeWidgetItem>
#include "sceneobject.h"

class GraphSceneItem : public QTreeWidgetItem
{
public:
	GraphSceneItem(Shapes::SceneObject* shapeItem);
	~GraphSceneItem();

	Shapes::SceneObject* getShape() const { return shape; };

private:
	Shapes::SceneObject* shape;
};

