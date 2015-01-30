#ifndef TEST_MAIN_CPP
#define TEST_MAIN_CPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <string>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "display/display.h"
#include "game/game.h"
#include "game/input_handler.h"
#include "mesh/wavefront.h"
#include "shader/shader.h"
#include "shader/shader_program.h"
#include "mesh/mesh_model.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;
static const std::string DISPLAY_NAME = "MY APP";

// static proxy function to propagate the key events to the display instance
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Inputhandler * inputhandler = reinterpret_cast<Inputhandler *>(glfwGetWindowUserPointer(window));
	inputhandler->HandleKey(key, scancode, action, mods);
}

int main () {

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_NAME);
	Wavefront mesh("monkey.obj");
	Inputhandler inputhandler(&display);
	
	Shader fragmentShader("shader.fragment", GL_FRAGMENT_SHADER);
	Shader vertexShader("shader.vertex", GL_VERTEX_SHADER);


	ShaderProgram program;

	program.Attach(fragmentShader.GetId());
	program.Attach(vertexShader.GetId());
	program.Link();

	// testing
	/*
        std::vector<float> vertexData;
        std::vector<GLuint> indexData;

	    vertexData.push_back(-0.5f);
	    vertexData.push_back(0.5f);
	    vertexData.push_back(0.0f);

	    vertexData.push_back(-0.5f);
	    vertexData.push_back(-0.5f);
	    vertexData.push_back(0.0f);

	    vertexData.push_back(0.5f);
	    vertexData.push_back(-0.5f);
	    vertexData.push_back(0.0f);

	    vertexData.push_back(0.5f);
	    vertexData.push_back(0.5f);
	    vertexData.push_back(0.0f);

	    indexData.push_back(0);
	    indexData.push_back(1);
	    indexData.push_back(3);
	    indexData.push_back(3);
	    indexData.push_back(1);
	    indexData.push_back(2);



        MeshModel mesh(vertexData, indexData);
	*/
	//--testing

	glfwSetWindowUserPointer(display.getWindow(), &inputhandler);
	glfwSetKeyCallback( display.getWindow(), keyCallback );

	while( !glfwWindowShouldClose( display.getWindow() ) ){

		display.Clear();
		//double time = glfwGetTime();
		program.Use();
		mesh.Bind();
        //wavefront.Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_INT, (void*)0);
        //glDrawArrays(GL_TRIANGLES, 0, 6); 

		display.Update();
	}

	return 0;
}

#endif