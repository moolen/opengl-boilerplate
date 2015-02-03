#ifndef TEST_INPUTHANDLER_CPP
#define TEST_INPUTHANDLER_CPP

#include <iostream>
#include "input_handler.h"

Inputhandler::Inputhandler(Display* display):
	m_display(display)
{
	//std::cout << "Inputhandler constructor" << std::endl;
}

void Inputhandler::HandleKey(int key, int scancode, int action, int mods){
	
	if( key == GLFW_KEY_A ){
		emit<int>(Inputhandler::A, mods);
	}

	if( key == GLFW_KEY_W ){
		emit<int>(Inputhandler::W, mods );
	}

	if( key == GLFW_KEY_S ){
		emit<int>(Inputhandler::S, mods);
	}

	if( key == GLFW_KEY_D ){
		emit<int>(Inputhandler::D, mods);
	}

	if (key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(m_display->getWindow(), 1);
		return;
	}



}

void Inputhandler::HandleMouse(double xpos, double ypos){

	double dx = (double) m_xpos - xpos;
	double dy = (double) m_ypos - ypos;

	emit<double, double>(Inputhandler::MOUSEMOVE, dx, dy);

	m_xpos = xpos;
	m_ypos = ypos;
}

Inputhandler::~Inputhandler(){
	//std::cout << "Inputhandler destructor" << std::endl;
}

#endif