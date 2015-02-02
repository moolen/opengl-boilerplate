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
#include "game/camera.h"

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
	Wavefront mesh("monkey-uv.obj");
	Texture texture("bricks.jpg");
	Inputhandler inputhandler(&display);
	double gametime = glfwGetTime();

	Shader fragmentShader("shader.fragment", GL_FRAGMENT_SHADER);
	Shader vertexShader("shader.vertex", GL_VERTEX_SHADER);
	ShaderProgram program;
	program.Attach(fragmentShader.GetId());
	program.Attach(vertexShader.GetId());
	program.Link();

	//program.AddUniform("in_Time");
	program.AddUniform("modelMatrix");
	program.AddUniform("projectionMatrix");
	program.AddUniform("viewMatrix");
	program.AddUniform("lightPosition");
	program.AddUniform("lightColor");

	Light light(
		glm::vec3(0, 0, 5), // position
		glm::vec3(1, 1, 1) // color
	);

	Camera camera(
		glm::vec3(0, 0, 3),
		65.0f,
		(float) DISPLAY_WIDTH / DISPLAY_HEIGHT,
		1.0f,
		100.0f
	);

	 glm::mat4 projectionMatrix = glm::perspective(
            65.0f,
            (float) DISPLAY_WIDTH / DISPLAY_HEIGHT,
            1.0f,
            100.0f
    );

	glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0, 0, 3),
        glm::vec3(0, 0, -5),
        glm::vec3(0, 1, 0)
    );

	glfwSetWindowUserPointer(display.getWindow(), &inputhandler);
	glfwSetKeyCallback( display.getWindow(), keyCallback );

	while( !glfwWindowShouldClose( display.getWindow() ) ){

		display.Clear();

		gametime = glfwGetTime();
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.5));
		modelMatrix = glm::rotate(modelMatrix, (float) gametime, glm::vec3(0, 1, 0));

		camera.MoveLeft(0.01f);
		camera.Update();

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
			camera.GetProjectionPtr()
		);

		glUniformMatrix4fv(
			program.GetUniformLocation("viewMatrix"),
			1,
			GL_FALSE,
			//&viewMatrix[0][0]
			&camera.GetView()[0][0]
		);

		glUniform3fv(
			program.GetUniformLocation("lightPosition"),
			1,
			light.GetPosition()
		);

		glUniform3fv(
			program.GetUniformLocation("lightColor"),
			1,
			light.GetColor()
		);

		glActiveTexture(GL_TEXTURE0);


		program.Use();
		texture.Bind();
		mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_INT, (void*)0);

		display.Update();
	}

	return 0;
}

#endif