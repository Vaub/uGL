#pragma once

#include <cstdio>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <thread>
#include <mutex>

#include <stdexcept>
#include <time.h> 

#include "material.h"

#include "shape.h"
#include "vertex.h"

typedef unsigned int uint;

class ImportShapeModel
{
public:

	ImportShapeModel(const std::string& fileName, uint bufferSize = 1024)
		: buffer(bufferSize)
	{
		fileStream = std::ifstream(fileName, std::ios::in);
		if (!fileStream) { throw std::invalid_argument("Impossible to open the file!"); }
		
		fileDirectory = fileName.substr(0, fileName.find_last_of("\\/"));

		importShape();
		createModel();
	}

	Shapes::Shape* getModel() const { return model; }

	// While it has a poorly choosen name, this is the representation of a Face in .obj files
	struct VertexIndices {
		int position = -1;
		int texCoord = -1;
		int normal = -1;
	};
	

private:
	std::string fileDirectory;

	std::ifstream fileStream; // it's how we read the file?
	std::ifstream mtlStream;

	std::vector<glm::vec3> modelPositions;
	std::vector<glm::vec3> modelNormals;
	std::vector<glm::vec2> modelTexCoords;
	std::vector<VertexIndices> modelFaces;

	uint buffer; // Number of lines to read each pass

	Shapes::Shape* model = 0;

	/*
	 * Import the shape
	 */
	void importShape();

	/*
	 * Import material files
	 */
	void importMaterials();

	/*
	 * Creates the model and does all kind of fancy stuff like averaging its normals
	 */
	void createModel();

	/*
	 * Read the ammount of lines specified in the buffer
	 */
	int getLines(std::vector<std::string>& content);

	/*
	 * Add contents to create the model
	 */
	void addContent(const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec3>& normals,
		const std::vector<glm::vec2>& texCoords,
		const std::vector<VertexIndices>& faces);

	/*
	 * Method to read the obj values, not sure about the sscanf speed though
	 */
	static std::vector<VertexIndices> readFaceValues(const std::string& face);

	
};

