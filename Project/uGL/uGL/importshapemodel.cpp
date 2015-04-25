#include "importshapemodel.h"

void ImportShapeModel::importShape()
{
	std::vector<std::string> lines;
	do
	{
		std::vector<VertexIndices> faces;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> positions;

		int currentToken = getLines(lines);
		for (std::string line : lines) // reads a bunch of lines
		{
			//if (line.substr(0, 7) == "mtllib ")
			//{
			//	std::istringstream s(line.substr(7));
			//	std::string mtlName; s >> mtlName;
			//
			//	mtlStream = std::ifstream(fileDirectory + "/" + mtlName);
			//	if (!mtlStream) { continue; }
			//
			//	importMaterials();
			//}
			if (line.substr(0, 2) == "v ") // in case we found a vertex (aka position)
			{
				std::istringstream s(line.substr(2));
				glm::vec3 p; s >> p.x; s >> p.y; s >> p.z;

				positions.push_back(p);
			}
			else if (line.substr(0, 3) == "vn ") { // a normal for a vertex
				std::istringstream s(line.substr(2));
				glm::vec3 n; s >> n.x; s >> n.y; s >> n.z;

				normals.push_back(n);
			}
			else if (line.substr(0, 3) == "vt ") {
				std::istringstream s(line.substr(2));
				glm::vec2 t; s >> t.x; s >> t.y;

				texCoords.push_back(t);
			}
			else if (line.substr(0, 2) == "f ") // a face (a mix of position/normal/texCoords)
			{
				try {
					std::vector<VertexIndices> triangle = readFaceValues(line.substr(2));
					faces.insert(faces.end(), triangle.begin(), triangle.end());
				}
				catch (...) {}
			}
		}

		addContent(positions, normals, texCoords, faces);

	} while (lines.size() > 0);
}

void ImportShapeModel::createModel()
{
	std::vector<Utilities::Vertex> vertices(modelPositions.size());
	std::vector<GLuint> indices;

	if (vertices.size() == 0) {
		throw std::runtime_error("Not a valid format!");
	}

	bool needToComputeNormals = false;
	std::vector<glm::vec3> normalAverage(vertices.size());
	std::vector<std::tuple<uint, glm::vec2>> texCoordsAverage(vertices.size());

	for (uint i = 0; i < modelFaces.size(); i++) {
		int vertexPos = modelFaces[i].position - 1;

		if (vertexPos < 0) { throw std::runtime_error("Can't parse the model. It might not be a supported format."); }
		indices.push_back(vertexPos);

		if (modelFaces[i].normal != -1) {
			normalAverage[vertexPos] += modelNormals[modelFaces[i].normal - 1];
		}
		else {
			needToComputeNormals = true;
		}


		if (modelFaces[i].texCoord != -1) {
			auto texInfo = texCoordsAverage[vertexPos];
			auto texCoordValue = std::get<1>(texInfo) +modelTexCoords[modelFaces[i].texCoord - 1];

			texCoordsAverage[vertexPos] = std::tuple<uint, glm::vec2>(++std::get<0>(texInfo), texCoordValue);
		}
	}

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position = modelPositions[i];
		vertices[i].normal = glm::normalize(normalAverage[i]);

		auto texInfo = texCoordsAverage[i];
		uint texNb = std::get<0>(texInfo);
		if (texNb != 0) {
			vertices[i].textureCoordinates = std::get<1>(texInfo) / (float)texNb;
		}
	}

	model = new Shapes::Shape(vertices, indices, needToComputeNormals);

	fileStream.close();
	mtlStream.close();

	modelFaces.clear();
	modelPositions.clear();
	modelTexCoords.clear();
	modelNormals.clear();
}

int ImportShapeModel::getLines(std::vector<std::string>& content) {
	int currentToken;

	content.clear();
	content.reserve(buffer);

	std::string line;
	while (content.size() < buffer && std::getline(fileStream, line))
	{
		content.push_back(line);
	}

	return currentToken;
}

void ImportShapeModel::addContent(const std::vector<glm::vec3>& positions,
	const std::vector<glm::vec3>& normals,
	const std::vector<glm::vec2>& texCoords,
	const std::vector<VertexIndices>& faces)
{
	modelPositions.insert(modelPositions.end(), positions.begin(), positions.end());
	modelNormals.insert(modelNormals.end(), normals.begin(), normals.end());
	modelTexCoords.insert(modelTexCoords.end(), texCoords.begin(), texCoords.end());
	modelFaces.insert(modelFaces.end(), faces.begin(), faces.end());
}

std::vector<ImportShapeModel::VertexIndices> ImportShapeModel::readFaceValues(const std::string& face)
{
	std::vector<ImportShapeModel::VertexIndices> faces(3);
	std::vector<uint> uvIndices(3);

	int matches = 0;

	matches = sscanf(face.c_str(), "%d %d %d",
		&faces[0].position,
		&faces[1].position,
		&faces[2].position);
	if (matches == 3)
	{
		return faces;
	}

	matches = sscanf(face.c_str(), "%d/%d %d/%d %d/%d",
		&faces[0].position, &faces[0].texCoord,
		&faces[1].position, &faces[1].texCoord,
		&faces[2].position, &faces[2].texCoord);
	if (matches == 6)
	{
		return faces;
	}

	matches = sscanf(face.c_str(), "%d//%d %d//%d %d//%d",
		&faces[0].position, &faces[0].normal,
		&faces[1].position, &faces[1].normal,
		&faces[2].position, &faces[2].normal);
	if (matches == 6)
	{
		return faces;
	}

	matches = sscanf(face.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
		&faces[0].position, &faces[0].texCoord, &faces[0].normal,
		&faces[1].position, &faces[1].texCoord, &faces[1].normal,
		&faces[2].position, &faces[2].texCoord, &faces[2].normal);
	if (matches == 9)
	{
		return faces;
	}

	throw std::invalid_argument("Not a valid face");
}

void ImportShapeModel::importMaterials()
{
	std::map<std::string, Shaders::Material> materialLines;

	std::string currentMaterial = "";

	std::string line;
	while (std::getline(mtlStream, line)) {
		if (line.substr(0, 6) == "newmtl") {
			std::istringstream s(line.substr(7));
			s >> currentMaterial;

			continue;
		}

		if (currentMaterial == "") { continue; }

		if (line.substr(0, 3) == "Ka ") {
			std::istringstream s(line.substr(3));
			glm::vec3 a; s >> a.x; s >> a.y; s >> a.z;

			materialLines[currentMaterial].lightColor.ambient = a;
		}
		else if (line.substr(0, 3) == "Kd ") {
			std::istringstream s(line.substr(3));
			glm::vec3 d; s >> d.x; s >> d.y; s >> d.z;

			materialLines[currentMaterial].lightColor.diffuse = d;
		}
		else if (line.substr(0, 3) == "Ks ") {
			std::istringstream s(line.substr(3));
			glm::vec3 spec; s >> spec.x; s >> spec.y; s >> spec.z;

			materialLines[currentMaterial].lightColor.specular = spec;
		}
		else if (line.substr(0, 3) == "Ns ") {
			std::istringstream s(line.substr(3));
			float shine; s >> shine;

			materialLines[currentMaterial].shineFactor = shine;
		}
	}
}