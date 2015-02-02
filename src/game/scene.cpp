#ifndef BOILERPLATE_SCENE_CPP
#define BOILERPLATE_SCENE_CPP

#include "scene.h"
#include "../util/file.h"
#include <iostream>


Scene::Scene(std::string name):
	m_path("resources/scenes/")
{
	std::string fullPath = m_path + name;
	File configuration(fullPath.c_str());
	std::cout << configuration.Get() << std::endl;
}

Scene::~Scene(){

}

#endif