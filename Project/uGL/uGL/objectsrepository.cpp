#include "objectsRepo.h"

ObjectsRepository::ObjectsRepository()
{
}

ObjectsRepository::~ObjectsRepository()
{
}

void ObjectsRepository::addShape(Shapes::SceneObject * newObject)
{
	handleNameRepetition(newObject);
	sceneObjects.push_back(newObject);
	emit repositoryChanged();
}

void ObjectsRepository::removeShape(Shapes::SceneObject* shape)
{
	throw std::invalid_argument("Not implemented");
}

void ObjectsRepository::removeShape(int index)
{
	if (index >= sceneObjects.size() - 1)
		throw std::invalid_argument("Cannot remove non-existent shape");
	sceneObjects.erase(sceneObjects.begin() + 1);
	emit repositoryChanged();
}

const std::vector<Shapes::SceneObject*>& ObjectsRepository::listsShapesInGraph() const
{
	return sceneObjects;
}

void ObjectsRepository::handleNameRepetition(Shapes::SceneObject* newObject)
{
	std::map<std::string, int>::iterator iterator;
	iterator = numberOfObjectsWithSameName.find(newObject->getName());
	bool objectWithSameNameAlreadyExists = (iterator != numberOfObjectsWithSameName.end());

	if (objectWithSameNameAlreadyExists)
	{
		numberOfObjectsWithSameName[newObject->getName()] = numberOfObjectsWithSameName[newObject->getName()] + 1;

		std::stringstream stringStream;
		stringStream << newObject->getName() << " " << numberOfObjectsWithSameName[newObject->getName()];
		std::string newName = stringStream.str();
		newObject->changeName(newName);
	}
	else
	{
		numberOfObjectsWithSameName[newObject->getName()] = 1;
	}
}