#ifndef TEST_MESH_MODEL_H
#define TEST_MESH_MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "glm/glm.hpp"

class MeshModel{
public:
	
	// VAO attribute list indices
	const static int VERTEX_ARRAY_POSITION = 0;
	const static int VERTEX_ARRAY_NORMAL = 1;
	const static int VERTEX_ARRAY_TEXTURE = 2;
	
	// constructor: nothing
	MeshModel();

	// constructor: pos only
	MeshModel(std::vector<GLfloat> positions);

	// position & indices
	MeshModel(
		std::vector<GLfloat> positions,
		std::vector<GLuint> indices
	);

	// constructor: pos, index, normal
	MeshModel(
		std::vector<GLfloat> positions,
		std::vector<GLuint> indices,
		std::vector<GLfloat> normals
	);

	// constructor: pos, index, normal, tex
	MeshModel(
		std::vector<GLfloat> positions,
		std::vector<unsigned int> indices,
		std::vector<GLfloat> normals,
		std::vector<GLfloat> texCoords
	);

	// setter for pos, norm, indices, tex
	void AddPositions(std::vector<GLfloat> positions);
	void AddNormals(std::vector<GLfloat> normals);
	void AddIndices(std::vector<GLuint> indices);
	void AddTextures(std::vector<GLfloat> textures);

	std::vector<GLfloat> CalculateNormals(
		std::vector<GLfloat> positions,
		std::vector<GLuint> indices
	);

	// std::vector<GLfloat> CalculateNormals(
	// 	std::vector<GLfloat> positions
	// );

	// (un)bind VAO
	void Bind();
	void Unbind();

	GLuint GetVAO();

	GLuint GetVertexCount();

	virtual ~MeshModel();

private:
	GLuint m_vaoID;
	unsigned int m_vertexCount;
	std::vector<GLuint> m_vbos;

	void SetVertexCount(int count);

	// actual storing procedures
	GLuint StoreIndexBuffer(std::vector<GLuint> data);
	GLuint StoreInAttributeList(
		GLuint target,
		GLuint attributeListPosition,
		std::vector<GLfloat> data,
		GLuint size
	);

	//
	// VAO STUFF
	// 
	void CreateVAO();
	void BindVAO();
	void UnbindVAO();
	void DeleteVAO();

	//
	//  VBO STUFF
	//
	void CreateVBO(GLuint* vboID);
	void BindVBO(GLuint target, GLuint vboID);
	void UnbindVBO(GLuint target);
	void DeleteVBO(GLuint* vboID);
};

#endif