#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "scene.h"
#include "event_emitter.h"
#include "input_handler.h"
#include "../display/display.h"
#include "camera.h"

class Game : public EventEmitter {
	public:
		Game(Display* display, Inputhandler* inputhandler);
		Camera* GetCamera();
		void Render();
		virtual ~Game();
	private:
		float m_moveSpeed;
		Display* m_display;
		Inputhandler* m_inputHandler;
		Scene m_scene;
		Camera m_camera;
};

#endif