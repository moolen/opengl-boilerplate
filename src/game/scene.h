#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <string>
#include <rapidjson/document.h>
#include "entityfactory.h"

class Scene{

public:
	Scene(std::string name);
	virtual ~Scene();
private:
	std::string m_path;
	rapidhson::Document m_document;
	EntityFactory m_entityFactory;
};

#endif