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
	if (key == GLFW_KEY_ESCAPE){
		glfwSetWindowShouldClose(m_display->getWindow(), 1);
		return;
	}

	

}

Inputhandler::~Inputhandler(){
	//std::cout << "Inputhandler destructor" << std::endl;
}

#endif