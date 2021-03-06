#ifndef TEST_SHADER_PROGRAM_CPP
#define TEST_SHADER_PROGRAM_CPP

#include "shader_program.h"
#include <iostream>
#include <stdio.h>

ShaderProgram::ShaderProgram():
	m_program(glCreateProgram())
{
	if(m_program == 0)
		std::cout << "error creating shader program" << std::endl;
	
	//std::cout << "shaderprogram constructor: " << m_program << std::endl;

}

void ShaderProgram::Attach(GLuint shaderId){
	glAttachShader(m_program, shaderId);
	//m_shaderIds.push_back(shaderId);
}

void ShaderProgram::Link(){
	printf("linking program #%d", m_program);
	glLinkProgram(m_program);
	Shader::CheckShaderError(m_program, GL_LINK_STATUS, true, "error linking shader");
	CheckInfoLog(m_program);
	glValidateProgram(m_program);
}

void ShaderProgram::Use(){
	glUseProgram(m_program);
}

GLint ShaderProgram::AddUniform(const char* uniform){
	GLint location = glGetUniformLocation(m_program, (const GLchar *) uniform);

	printf("uniform location: %d for %s\n", location, uniform);

	if( location == GL_INVALID_VALUE || location == -1){
		printf("invalid uniform location for %s\n", uniform);
		return GL_INVALID_VALUE;
	}else{
		m_uniforms.insert(std::pair<const char*,int>(uniform, location));
		return location;
	}
}

GLint ShaderProgram::GetUniformLocation(const char* uniform){
	return m_uniforms.find(uniform)->second;
}

void ShaderProgram::CheckInfoLog(GLuint program){
    int InfoLogLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
    }
}

ShaderProgram::~ShaderProgram(){
	//std::cout << "shaderprogram destructor" << std::endl;
	glDeleteProgram(m_program);
}

#endif