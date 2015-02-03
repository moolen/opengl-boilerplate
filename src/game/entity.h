#ifndef BOILERPLATE_ENTITY_H
#define BOILERPLATE_ENTITY_H

#include <glm/glm.hpp>
#include "../mesh/mesh_model.h"
#include "../mesh/texture.h"
#include "../shader/shader_program.h"
#include "camera.h"

class Entity
{
public:
	Entity(
		MeshModel model,
		ShaderProgram* program,
		Texture texture,
		glm::vec3 position
	);
	void Render(Camera* camera);
	~Entity();
	
protected:
	MeshModel m_model;
	glm::vec3 m_position;
	ShaderProgram* m_program;
	Texture m_texture;
	glm::mat4 m_modelMatrix;

};

#endif