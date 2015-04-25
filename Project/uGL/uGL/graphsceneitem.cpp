#include "graphSceneItem.h"

GraphSceneItem::GraphSceneItem(Shapes::SceneObject* shapeItem)
{
	this->shape = shapeItem;
	this->setText(0, shapeItem->getName().c_str());
}

GraphSceneItem::~GraphSceneItem()
{
}
