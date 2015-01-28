#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "scene.h"

class Game{
	public:
		Game();
		virtual ~Game();
	private:
		Scene m_scene;
};

#endif