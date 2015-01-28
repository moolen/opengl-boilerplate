#ifndef TEST_MESH_H
#define TEST_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "mesh_model.h"

struct Vertex{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos(){ return &pos; }
	glm::vec2* GetTexCoord(){ return &texCoord; }
	glm::vec3* GetNormal(){ return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

};

struct Material
{
public:
	Material(const glm::vec4& d, const glm::vec4& a, const glm::vec4& s, const glm::vec4& e, const float& sh)
	{
		diffuse = d;
		ambient = a;
		specular = s;
		emissive = e;
		shininess = sh;
	}

	glm::vec4 getDiffuse(){ return diffuse; }
	glm::vec4 getAmbient(){ return ambient; }
	glm::vec4 getSpecular(){ return specular;	}
	glm::vec4 getEmissive(){ return emissive;	}
	float getShininess(){ return shininess; }

private:
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 specular;
	glm::vec4 emissive;
	float shininess;

};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh{
public:
	Mesh();
	void Draw();
	virtual ~Mesh();
private:
	static const unsigned int NUM_BUFFERS = 4;
	GLuint m_VAO;
	GLuint m_VAB[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif