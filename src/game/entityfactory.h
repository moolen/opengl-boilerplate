#ifndef BOILERPLATE_ENTITYFACTORY_H
#define BOILERPLATE_ENTITYFACTORY_H

#include "entity.h"
#include <vector>

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

protected:
	std::vector<Entity*> m_entitites;

};

#endif