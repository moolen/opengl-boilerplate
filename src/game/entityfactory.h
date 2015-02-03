#ifndef BOILERPLATE_ENTITYFACTORY_H
#define BOILERPLATE_ENTITYFACTORY_H

#include "entity.h"
#include "loader.h"
#include <vector>

class EntityFactory
{
public:
	EntityFactory();
	EntityFactory(Loader* loader);
	void CreateEntity(
		glm::vec3 position,
		std::string meshType,
		std::string mesh,
		std::string texture,
		std::string fragmentShader,
		std::string vertexShader
	);

	std::vector<Entity> GetEntities();

	void SetLoader(Loader* loader);

	~EntityFactory();

protected:
	std::vector<Entity> m_entities;
	Loader* m_loader;

};

#endif