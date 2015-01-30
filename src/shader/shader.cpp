#ifndef TEST_SHADER_CPP
#define TEST_SHADER_CPP

#include "shader.h"
#include "../util/file.h"
#include <iostream>
#include <vector>
#include <stdio.h>

Shader::Shader(const char* filename, GLuint type):
m_path("resources/shaders/"),
m_shaderType(type),
m_filename(filename)
{
	//std::cout << "shader constructor" << std::endl;
	ReadShaderfile();
	CompileShader();
}

std::string Shader::ReadShaderfile(){
	std::string fullPath = m_path + m_filename;
	File file(fullPath.c_str());
	m_shaderSource = file.Get();
	return m_shaderSource;
}

std::string Shader::GetShaderSource(){
	return m_shaderSource.c_str();
}

GLuint Shader::GetId(){
	return m_shaderId;
}

GLuint Shader::CompileShader()
{
	m_shaderId = glCreateShader(m_shaderType);

	printf("compiling shader %d: %s \n", m_shaderId, m_filename.c_str());
	char const* shaderSourcePointer = m_shaderSource.c_str();

	glShaderSource(m_shaderId, 1, &shaderSourcePointer, NULL);
	glCompileShader(m_shaderId);
	CheckShaderError(m_shaderId, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return m_shaderId;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = GL_FALSE;
	GLchar error[1024] = { 0 }; 

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << errorMessage << ": '" << error << "'" << std::endl;
	}
}

Shader::~Shader(){
	glDeleteShader(m_shaderId);
	//std::cout << "shader destructor" << std::endl;
}

#endif