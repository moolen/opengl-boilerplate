#ifndef BOILERPLATE_LOADER_CPP
#define BOILERPLATE_LOADER_CPP

#include "loader.h"
#include <iostream>


ShaderProgram* Loader::LoadProgram(
	std::string vertexShader,
	std::string fragmentShader)
{

	std::string fullShader = vertexShader + std::string("-") + fragmentShader;

	// if shader does exist
	if( m_programs.find(fullShader) != m_programs.end() ){
		return m_programs.at(fullShader);
	} // otherwise create 
	else{
		const char* vs = vertexShader.c_str();
		const char* fs = fragmentShader.c_str();
		
		// create instances
		Shader vertexShader( vs, GL_VERTEX_SHADER );
		Shader fragmentShader( fs, GL_FRAGMENT_SHADER);
		ShaderProgram* program = new ShaderProgram();

		//attach shaders to prg
		program->Attach(fragmentShader.GetId());
		program->Attach(vertexShader.GetId());

		//link
		program->Link();

		//insert into map
		m_programs.insert(
			std::map<std::string, ShaderProgram*>::value_type(fullShader, program)
		);

		return program;
	}

}

Loader::Loader(){}
Loader::~Loader(){
	std::map<std::string, ShaderProgram*>::iterator it;
	for( it = m_programs.begin(); it != m_programs.end(); ++it ){
		delete it->second;
		m_programs.erase(it);
	}
}


#endif