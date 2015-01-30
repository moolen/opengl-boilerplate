#ifndef TEST_MAIN_CPP
#define TEST_MAIN_CPP

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
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
	double gametime = glfwGetTime();
	Shader fragmentShader("shader.fragment", GL_FRAGMENT_SHADER);
	Shader vertexShader("shader.vertex", GL_VERTEX_SHADER);
	ShaderProgram program;
	program.Attach(fragmentShader.GetId());
	program.Attach(vertexShader.GetId());
	program.Link();

	program.AddUniform("in_Time");
	program.AddUniform("modelMatrix");
	program.AddUniform("projectionMatrix");
	program.AddUniform("viewMatrix");

	glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, -5),
		glm::vec3(0, 1, 0)
	);

	glm::mat4 projectionMatrix = glm::perspective(
		65.0f,
		(float) DISPLAY_WIDTH / DISPLAY_HEIGHT,
		1.0f,
		100.0f
	);

	glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), (float) gametime, glm::vec3(0.0f, 1.0f, 0.0f));

	//--testing
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
		gametime = glfwGetTime();
		glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), (float) gametime, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniform1f(
			program.GetUniformLocation("in_Time"), (float) gametime
		);

		glUniformMatrix4fv(
			program.GetUniformLocation("modelMatrix"),
			1,
			GL_FALSE,
			&modelMatrix[0][0]
		);

		glUniformMatrix4fv(
			program.GetUniformLocation("projectionMatrix"),
			1,
			GL_FALSE,
			&projectionMatrix[0][0]
		);

		glUniformMatrix4fv(
			program.GetUniformLocation("viewMatrix"),
			1,
			GL_FALSE,
			&viewMatrix[0][0]
		);


		program.Use();
		mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_INT, (void*)0);

		display.Update();
	}

	return 0;
}

#endif