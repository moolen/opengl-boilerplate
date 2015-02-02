#ifndef TEST_MESH_MODEL_CPP
#define TEST_MESH_MODEL_CPP

#include "mesh_model.h"
#include <stdio.h>
#include <iostream>

//
//
//  CONSTRUCTORS
//
//

// empty constructor
// @use AddPositions / AddNormals / AddIndices
MeshModel::MeshModel(){}

/**
 * constructor:
 * - positions only
 */
MeshModel::MeshModel(
	std::vector<GLfloat> positions)
{
	SetVertexCount(positions.size() / 3);
	CreateVAO();
	BindVAO();
	
	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		0,
		positions,
		3
	);
	
	UnbindVAO();

}

/**
 * constructor:
 * - positions
 * - indices
 */
MeshModel::MeshModel(
	std::vector<GLfloat> positions,
	std::vector<GLuint> indices
)
{
	SetVertexCount(indices.size());
	CreateVAO();
	BindVAO();
	
	StoreIndexBuffer(indices);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		0,
		positions,
		3
	);

	
	UnbindVAO();

}

/**
 * constructor:
 * - positions
 * - indices
 * - normals
 */
MeshModel::MeshModel(
	std::vector<GLfloat> positions,
	std::vector<GLuint> indices,
	std::vector<GLfloat> normals
)
{
	SetVertexCount(indices.size());
	CreateVAO();
	BindVAO();
	
	StoreIndexBuffer(indices);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_POSITION,
		positions,
		3
	);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_NORMAL,
		normals,
		3
	);

	
	UnbindVAO();

}

/**
 * Constructr:
 * - positions
 * - indices
 * - normals
 * - texCoords
 */
MeshModel::MeshModel(
	std::vector<GLfloat> positions,
	std::vector<unsigned int> indices,
	std::vector<GLfloat> normals,
	std::vector<GLfloat> texCoords
)
{
	SetVertexCount(indices.size());
	CreateVAO();
	BindVAO();
	
	StoreIndexBuffer(indices);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_POSITION,
		positions,
		3
	);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_NORMAL,
		normals,
		3
	);

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_TEXTURE,
		texCoords,
		2
	);

	
	UnbindVAO();

}


void MeshModel::AddPositions(std::vector<GLfloat> positions){
	
	SetVertexCount(positions.size() / 3);
	if(!m_vaoID){
		CreateVAO();
	}

	BindVAO();
	StoreInAttributeList(GL_ARRAY_BUFFER, VERTEX_ARRAY_POSITION, positions, 3);

	UnbindVAO();
}

void MeshModel::AddNormals(std::vector<GLfloat> normals){
	if(!m_vaoID){
		CreateVAO();
	}
	BindVAO();
	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_NORMAL,
		normals,
		3
	);
	UnbindVAO();
}

void MeshModel::AddIndices(std::vector<GLuint> indices){
	if(!m_vaoID){
		std::cout << "adding vao again" << std::endl;
		CreateVAO();
	}
	SetVertexCount(indices.size());
	BindVAO();

	StoreIndexBuffer(indices);

	UnbindVAO();
}

void MeshModel::AddTextures(std::vector<GLfloat> textures){
	if( !m_vaoID ){
		std::cout << "adding vao again" << std::endl;
		CreateVAO();
	}
	BindVAO();

	StoreInAttributeList(
		GL_ARRAY_BUFFER,
		VERTEX_ARRAY_TEXTURE,
		textures,
		2
	);
	UnbindVAO();
}

GLuint MeshModel::GetVAO(){
	return m_vaoID;
}

/**
 * MeshModel::StoreInAttributeList
 * - stores data in a attribute list
 * 
 * @param  target
 * @param  attributeListPosition
 * @param  data
 * @param  size
 * @return GLuint
 */
GLuint MeshModel::StoreInAttributeList(
	GLuint target,
	GLuint attributeListPosition,
	std::vector<GLfloat> data,
	GLuint size)
{

	GLuint vertexbuffer;
    CreateVBO(&vertexbuffer);
    BindVBO(target, vertexbuffer);

    glBufferData(
    	target,
    	data.size() * sizeof(GLfloat),
    	&data[0],
    	GL_STATIC_DRAW
    );
    
    glVertexAttribPointer(
            attributeListPosition,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            size,               // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(attributeListPosition);
	return vertexbuffer;
}

GLuint MeshModel::StoreIndexBuffer(std::vector<GLuint> indices)
{
	GLuint indexBufferID;
	CreateVBO(&indexBufferID);
	BindVBO(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	std::cout << "index vbo: " << indexBufferID << std::endl;

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		&indices[0],
		GL_STATIC_DRAW
	);
}

//
//
//  PUBLIC (UN)BIND VAO
//
//

void MeshModel::Bind(){
	glBindVertexArray(m_vaoID);
}

void MeshModel::Unbind(){
	glBindVertexArray(0);
}

//
//
//   VBO STUFF
//
//

void MeshModel::CreateVBO(GLuint* vboID){
	glGenBuffers(1, vboID);
}

void MeshModel::BindVBO(GLuint target, GLuint vboID){
	glBindBuffer(target, vboID);
}

void MeshModel::UnbindVBO(GLuint target){
	glBindBuffer(target, 0);
}

void MeshModel::DeleteVBO(GLuint* vboID){
	glDeleteBuffers(1, vboID);
}

//
//
//   VAO STUFF
//
//

void MeshModel::CreateVAO(){
	glGenVertexArrays(1, &m_vaoID);
}

void MeshModel::BindVAO(){
	glBindVertexArray(m_vaoID);
}

void MeshModel::UnbindVAO(){
	glBindVertexArray(0);
}

void MeshModel::DeleteVAO(){
	glDeleteVertexArrays(1, &m_vaoID);
}



void MeshModel::SetVertexCount(int count){
	m_vertexCount = count;
}

GLuint MeshModel::GetVertexCount(){
	return m_vertexCount;
}





MeshModel::~MeshModel(){
	
	for(std::vector<GLuint>::size_type i = 0; i != m_vbos.size(); i++){
		DeleteVBO(&m_vbos[i]);
	}

	DeleteVAO();

}

#endif