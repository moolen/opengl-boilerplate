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

	std::cout << "shape count: " << shapes.size() << std::endl;;

	std::vector<GLfloat> positions;
	std::vector<GLuint> indices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;

	for (size_t i = 0; i < shapes.size(); i++) {
	  
		printf("normals: %i \n", shapes[i].mesh.normals.size());
		printf("texcoords: %i \n", shapes[i].mesh.texcoords.size());
		printf("positions: %i \n", shapes[i].mesh.positions.size());
		printf("indices: %i \n", shapes[i].mesh.indices.size());

		indices.insert(
			indices.end(),
			shapes[i].mesh.indices.begin(),
			shapes[i].mesh.indices.end()
		);

	  	positions.insert(
	  		positions.end(),
	  		shapes[i].mesh.positions.begin(),
	  		shapes[i].mesh.positions.end()
	  	);

  		normals.insert(
	  		normals.end(),
	  		shapes[i].mesh.normals.begin(),
	  		shapes[i].mesh.normals.end()
	  	);

	  	texcoords.insert(
	  		texcoords.end(),
	  		shapes[i].mesh.texcoords.begin(),
	  		shapes[i].mesh.texcoords.end()
	  	);

	}

	m_model.AddPositions( positions );
	m_model.AddIndices( indices );
	m_model.AddNormals( normals );
	m_model.AddTextures( texcoords );

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