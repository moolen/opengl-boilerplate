#ifndef BOILERPLATE_LOADER_H
#define BOILERPLATE_LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include <vector>
#include <map>
#include <string>

#include "../shader/shader.h"
#include "../shader/shader_program.h"

class Loader{
public:
	Loader();
	virtual ~Loader();
	ShaderProgram* LoadProgram(
		std::string vertexShader,
		std::string fragmentShader
	);
protected:

	std::map<std::string, ShaderProgram*> m_programs;
};

#endif