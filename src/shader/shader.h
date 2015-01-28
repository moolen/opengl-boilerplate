#ifndef TEST_SHADER_H
#define TEST_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

class Shader{
public:
	Shader(const char* filename, GLuint type);
	
	// uniform api
	GLint AddUniform(const char* uniform);
	GLint GetUniformLocation(const char* uniform);
	void Uniform1i(const char* uniform, int value);
	void Uniform1f(const char* uniform, float value);
	
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
	std::map<const char*, GLint> m_uniforms;
	GLuint m_shaderType;
	GLuint m_shaderId;

	std::string ReadShaderfile();
	GLuint CompileShader();


};

#endif