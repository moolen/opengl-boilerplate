#ifndef BOILERPLATE_GAME_CPP
#define BOILERPLATE_GAME_CPP

#include "game.h"
#include <iostream>

Game::Game(
	Display* display,
	Inputhandler* inputhandler
):
m_display(display),
m_camera(
	glm::vec3(0, 0, 3),
	65.0f,
	display->getAspectRatio(),
	1.0f,
	10.0f
),
m_moveSpeed(0.3),
m_scene("example.json", &m_camera, inputhandler),
m_inputHandler(inputhandler)
{
	std::function<void(int)> forwardCallback = [=](int mods){
		this->GetCamera()->MoveForward(this->m_moveSpeed);
	};

	std::function<void(int)> backwardCallback = [=](int mods){
		this->GetCamera()->MoveBackward(this->m_moveSpeed);
	};

	std::function<void(int)> leftCallback = [=](int mods){
		this->GetCamera()->MoveLeft(this->m_moveSpeed);
	};

	std::function<void(int)> rightCallback = [=](int mods){
		this->GetCamera()->MoveRight(this->m_moveSpeed);
	};

	std::function<void(double, double)> mouseMoveCallback = [=](double dx, double dy){
		this->GetCamera()->Rotate(dx);
		this->GetCamera()->Pitch(dy);
	};

	m_inputHandler->on<int>(Inputhandler::W, forwardCallback);
	m_inputHandler->on<int>(Inputhandler::S, backwardCallback);
	m_inputHandler->on<int>(Inputhandler::A, leftCallback);
	m_inputHandler->on<int>(Inputhandler::D, rightCallback);
	m_inputHandler->on<double, double>(Inputhandler::MOUSEMOVE, mouseMoveCallback);
}

void Game::Render(){
	m_inputHandler->HandleKey(0, 0, 0, 0);
	m_scene.Render();
}

Camera* Game::GetCamera(){
	return &m_camera;
}

Game::~Game(){
	
}

#endif