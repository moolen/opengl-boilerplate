#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include "entityfactory.h"
#include "input_handler.h"
#include "loader.h"
#include "light.h"
#include "camera.h"

class Scene{

public:
	Scene(
		const char* name,
		Camera* camera,
		Inputhandler* inputhandler
	);
	void Render();
	virtual ~Scene();

protected:
	void AddLight(glm::vec3 pos, glm::vec3 color);
	std::vector<Light> m_lights;
private:
	const char* m_name;
	std::string m_path;
	Camera* m_camera;
	Inputhandler* m_inputHandler;
	rapidjson::Document m_document;
	EntityFactory m_entityFactory;
	Loader m_loader;
};

#endif