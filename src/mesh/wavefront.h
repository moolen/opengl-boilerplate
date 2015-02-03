#ifndef TEST_WAVEFRONT_H
#define TEST_WAVEFRONT_H

#include <string>
#include <vector>
#include "../util/file.h"
#include "mesh_model.h"
#include "tiny_obj_loader.h"

class Wavefront{
public:
	Wavefront(std::string filename);
	void Bind();
	int GetVertexCount();
	MeshModel GetModel();
	virtual ~Wavefront();
protected:
	std::string m_path;
	std::string m_filename;
	std::vector<tinyobj::shape_t> m_shapes;
	std::vector<tinyobj::material_t> m_materials;
	MeshModel m_model;
};

#endif