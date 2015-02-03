#ifndef BOILERPLATE_ENTITYFACTORY_CPP
#define BOILERPLATE_ENTITYFACTORY_CPP

#include "entityfactory.h"
#include "../mesh/wavefront.h"

EntityFactory::EntityFactory()
{

}

EntityFactory::EntityFactory(Loader* loader):
m_loader(loader)
{

}

void EntityFactory::CreateEntity(
		glm::vec3 position,
		std::string meshType,
		std::string meshFile,
		std::string textureFile,
		std::string fragmentShaderFile,
		std::string vertexShaderFile
	)
{

	// @TODO add more meshTypes 
	Wavefront newMesh(meshFile);

	Texture texture(textureFile);

	ShaderProgram* program = m_loader->LoadProgram(vertexShaderFile, fragmentShaderFile);
	program->Use();

	program->AddUniform("modelMatrix");
	program->AddUniform("projectionMatrix");
	program->AddUniform("viewMatrix");

	Entity newEntity(
		newMesh.GetModel(),
		program,
		texture,
		position
	);

	m_entities.push_back(newEntity);
}

std::vector<Entity> EntityFactory::GetEntities(){
	return m_entities;
}

void EntityFactory::SetLoader(Loader* loader){
	m_loader = loader;
}

EntityFactory::~EntityFactory(){
}

#endif