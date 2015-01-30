#ifndef TEST_SHADER_H
#define TEST_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

class Shader{
public:
	Shader(const char* filename, GLuint type);
	
	// getter
	std::string GetShaderSource();
	GLuint GetId();
	virtual ~Shader();

	// public static error checker
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

protected:;
	std::string m_path;
	std::string m_filename;
	std::string m_shaderSource;
	GLuint m_shaderType;
	GLuint m_shaderId;

	std::string ReadShaderfile();
	GLuint CompileShader();


};

#endif