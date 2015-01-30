#ifndef TEST_WAVEFRONT_CPP
#define TEST_WAVEFRONT_CPP

#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "wavefront.h"

Wavefront::Wavefront(std::string filename):
	m_path("resources/meshes/"),
	m_filename(filename),
	m_model()
{
	//std::cout << "Wavefront constructor" << std::endl;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string fullPath = m_path + m_filename;
	std::string err = tinyobj::LoadObj(shapes, materials, fullPath.c_str());

	if(!err.empty()){
		std::cerr << err << std::endl;
		exit(1);
	}

	std::cout << "shape count: " << shapes.size();

	m_model.AddPositions(shapes[0].mesh.positions);
	m_model.AddIndices(shapes[0].mesh.indices);
	m_model.AddNormals(shapes[0].mesh.normals);


}

int Wavefront::GetVertexCount(){
	return m_model.GetVertexCount();
}

void Wavefront::Bind(){
	m_model.Bind();
}

Wavefront::~Wavefront(){
	//std::cout << "Wavefront destructor" << std::endl;
}

#endif