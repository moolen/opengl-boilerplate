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

#include "display/display.h"
#include "game/game.h"
#include "game/input_handler.h"
#include "mesh/wavefront.h"
#include "shader/shader.h"
#include "shader/shader_program.h"

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
	//Wavefront mesh("cube.obj");
	Inputhandler inputhandler(&display);
	
	Shader fragmentShader("shader.fragment", GL_FRAGMENT_SHADER);
	Shader vertexShader("shader.vertex", GL_VERTEX_SHADER);


	ShaderProgram program;

	program.Attach(fragmentShader.GetId());
	program.Attach(vertexShader.GetId());
	program.Link();

	vertexShader.AddUniform("ftime");


	// testing
	// Dark blue background
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        static const GLfloat g_vertex_buffer_data[] = { 
                -1.0f, -1.0f, 0.0f,
                 1.0f, -1.0f, 0.0f,
                 0.0f,  1.0f, 0.0f,
        };

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &vertexbuffer);
	//--testing

	glfwSetWindowUserPointer(display.getWindow(), &inputhandler);
	glfwSetKeyCallback( display.getWindow(), keyCallback );

	while( !glfwWindowShouldClose( display.getWindow() ) ){

		display.Clear();
		double time = glfwGetTime();
		vertexShader.Uniform1f( "ftime", (float) time );
		program.Use();
		
		//
        glBindVertexArray(VertexArrayID);
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		display.Update();
	}

	return 0;
}

#endif