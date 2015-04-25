#pragma once

#include "QObject"
#include "sceneobject.h"
#include <sstream>   
#include <vector>

class ObjectsRepository : public QObject
{
	Q_OBJECT

public:
	ObjectsRepository();
	~ObjectsRepository();

	virtual void addShape(Shapes::SceneObject * newObject);

	virtual void removeShape(Shapes::SceneObject* shape);
	virtual void removeShape(int index);

	virtual const std::vector<Shapes::SceneObject*>& listsShapesInGraph() const;

signals:
	void repositoryChanged();

private:
	std::vector<Shapes::SceneObject*> sceneObjects;
	void handleNameRepetition(Shapes::SceneObject* newObject);
	std::map<std::string, int> numberOfObjectsWithSameName;
};

