#ifndef BOILERPLATE_ENTITY_H
#define BOILERPLATE_ENTITY_H

#include "../mesh/mesh_model.h"
#include "../mesh/texture.h"
#include "../shader/shader_program.h"

class Entity
{
public:
	Entity();
	~Entity();
	
protected:
	MeshModel m_model;
	ShaderProgram m_program;
	Texture m_texture;

};

#endif