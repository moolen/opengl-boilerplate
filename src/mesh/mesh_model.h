#ifndef TEST_MESH_MODEL_H
#define TEST_MESH_MODEL_H

#include <vector>
#include "glm/glm.hpp"

class MeshModel{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	std::vector<unsigned int> indices;
	MeshModel();
	virtual ~MeshModel();
private:
};

#endif