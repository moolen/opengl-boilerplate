#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "scene.h"
#include "camera.h"

class Game{
	public:
		Game();
		virtual ~Game();
	private:
		Scene m_scene;
		Camera m_camera;
};

#endif