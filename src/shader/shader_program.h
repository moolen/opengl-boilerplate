#ifndef TEST_SHADER_PROGRAM_H
#define TEST_SHADER_PROGRAM_H

#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <vector>

class ShaderProgram{
public:
	ShaderProgram();
	void Attach(GLuint shaderId);
	void Link();
	void Use();
	static void CheckInfoLog(GLuint program);
	virtual ~ShaderProgram();
protected:
	GLuint m_program;
	//std::vector<GLuint> m_shaderIds;
};

#endif