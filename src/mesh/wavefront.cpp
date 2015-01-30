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
	std::cout << "Wavefront constructor" << std::endl;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string fullPath = m_path + m_filename;
	std::string err = tinyobj::LoadObj(shapes, materials, fullPath.c_str());

	if(!err.empty()){
		std::cerr << err << std::endl;
		exit(1);
	}

	std::cout << shapes.size();

	std::vector<GLfloat> positions = shapes[0].mesh.positions;
	/*
	std::vector<float> vertexData;
    std::vector<GLuint> indexData;

    vertexData.push_back(-0.5f);
    vertexData.push_back(0.5f);
    vertexData.push_back(0.0f);

    vertexData.push_back(-0.5f);
    vertexData.push_back(-0.5f);
    vertexData.push_back(0.0f);

    vertexData.push_back(0.5f);
    vertexData.push_back(-0.5f);
    vertexData.push_back(0.0f);

    vertexData.push_back(0.5f);
    vertexData.push_back(0.5f);
    vertexData.push_back(0.0f);

    indexData.push_back(0);
    indexData.push_back(1);
    indexData.push_back(3);
    indexData.push_back(3);
    indexData.push_back(1);
    indexData.push_back(2);
*/
	m_model.AddPositions(shapes[0].mesh.positions);
	m_model.AddIndices(shapes[0].mesh.indices);

	// std::vector<GLuint> indices;
	// indices.push_back(0);
	// indices.push_back(1);
	// indices.push_back(3);
	// indices.push_back(3);
	// indices.push_back(1);
	// indices.push_back(2);

	// m_model.AddIndices(indices);

	for (size_t i = 0; i < shapes.size(); i++) {
	  printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
	  printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
	  printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
	  assert((shapes[i].mesh.indices.size() % 3) == 0);
	  
	  // map indices -> vertex
	  for( size_t idx = 0; idx < shapes[i].mesh.indices.size(); idx++ ){
	  	
	  	unsigned int vertexId = shapes[i].mesh.indices[idx];
	  	
	  	glm::vec3 currentPosition;

	  	currentPosition.x = shapes[i].mesh.positions[vertexId];
	  	currentPosition.y = shapes[i].mesh.positions[vertexId + 1];
	  	currentPosition.z = shapes[i].mesh.positions[vertexId + 2];

	  	//m_model.positions.push_back( currentPosition );

	  	printf("%i vertex: %f %f %f\n", vertexId, currentPosition.x, currentPosition.y, currentPosition.z);
	  }

	  // map normals
	  for( size_t idx = 0; idx < shapes[i].mesh.normals.size() / 3; idx++ ){
	  		  	
	  	glm::vec3 currentNormal;

	  	currentNormal.x = shapes[i].mesh.positions[3*idx + 0];
	  	currentNormal.y = shapes[i].mesh.positions[3*idx + 1];
	  	currentNormal.z = shapes[i].mesh.positions[3*idx + 2];

	  	//m_model.normals.push_back( currentNormal );

	  	printf("%i normal: %f %f %f\n",idx, currentNormal.x, currentNormal.y, currentNormal.z);

	  }

	}

}

int Wavefront::GetVertexCount(){
	return m_model.GetVertexCount();
}

void Wavefront::Bind(){
	m_model.Bind();
}

Wavefront::~Wavefront(){
	std::cout << "Wavefront destructor" << std::endl;
}

#endif