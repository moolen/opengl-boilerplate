#ifndef TEST_MAIN_CPP
#define TEST_MAIN_CPP

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "display/display.h"
#include "game/game.h"
#include "game/input_handler.h"
#include "mesh/wavefront.h"
#include "shader/shader.h"
#include "shader/shader_program.h"
#include "mesh/mesh_model.h"
#include "mesh/texture.h"
#include "game/light.h"
#include "game/debug.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;
static const std::string DISPLAY_NAME = "MY APP";

// static proxy function to propagate the key events to the display instance
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Inputhandler* inputhandler = reinterpret_cast<Inputhandler*>(glfwGetWindowUserPointer(window));
	inputhandler->HandleKey(key, scancode, action, mods);
}

// static proxy function to propagate the mouse position events to the display instance
static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos){
	Inputhandler* inputhandler = reinterpret_cast<Inputhandler*>(glfwGetWindowUserPointer(window));
	inputhandler->HandleMouse(xpos, ypos);
}

int main () {

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_NAME);
	Debug debug;
	Inputhandler inputhandler(&display);
	double gametime = glfwGetTime();

	Game game(&display, &inputhandler);

	Light light(
		glm::vec3(0, 0, 5), // position
		glm::vec3(1, 1, 1) // color
	);

	glfwSetWindowUserPointer(display.getWindow(), &inputhandler);
	glfwSetKeyCallback( display.getWindow(), keyCallback );
	glfwSetCursorPosCallback(display.getWindow(), mouseMoveCallback);

	while( !glfwWindowShouldClose( display.getWindow() ) ){
		display.Clear();
		debug.RenderAxis();
        game.Render();
		display.Update();
	}

	return 0;
}

#endif