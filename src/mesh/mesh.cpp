#ifndef TEST_MESH_CPP
#define TEST_MESH_CPP

#include <iostream>
#include "mesh.h"

Mesh::Mesh(){
	std::cout << "Mesh constructor" << std::endl;
}

Mesh::~Mesh(){
	std::cout << "Mesh destructor" << std::endl;
}

#endif