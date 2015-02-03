#ifndef BOILERPLATE_ENTITY_CPP
#define BOILERPLATE_ENTITY_CPP

#include "entity.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity(
	MeshModel model,
	ShaderProgram* program,
	Texture texture,
	glm::vec3 position
):
m_modelMatrix(glm::mat4(1.0f)),
m_model(model),
m_program(program),
m_texture(texture),
m_position(position)
{

	m_modelMatrix = glm::translate(m_modelMatrix, position);

}

void Entity::Render(Camera* camera){

	double gametime = glfwGetTime();
	
	m_program->Use();
	m_texture.Bind();
	m_model.Bind();
	

	//m_modelMatrix = glm::rotate(m_modelMatrix, (float) gametime, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(
		m_program->GetUniformLocation("modelMatrix"),
		1,
		GL_FALSE,
		&m_modelMatrix[0][0]
	);

	glUniformMatrix4fv(
			2,
			1,
			GL_FALSE,
			camera->GetProjectionPtr()
		);

		glUniformMatrix4fv(
			1,
			1,
			GL_FALSE,
			//&viewMatrix[0][0]
			camera->GetViewPtr()
		);

	//m_program->Use();

	glActiveTexture(GL_TEXTURE0);

	
	glDrawElements(GL_TRIANGLES, m_model.GetVertexCount(), GL_UNSIGNED_INT, (void*) 0);

	m_model.Unbind();
	m_texture.Unbind();
}

Entity::~Entity(){
	
}

#endif