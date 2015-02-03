#ifndef BOILERPLATE_TEXTURE_CPP
#define BOILERPLATE_TEXTURE_CPP

#include "texture.h"
#include "../util/stb_image.c"
#include <iostream>

Texture::Texture(const std::string filename):
	m_path("resources/textures/")
{
	int width, height, components;
	std::string fullPath = m_path + filename;

	unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &components, 4);

	if( data == NULL ){
		std::cerr << "Unable to load texture: " << fullPath << std::endl;
		return;
	}

	glGenTextures(1, &m_textureID);
	Bind();

	// texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

}

void Texture::Bind(){
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(){
	glDeleteTextures(1, &m_textureID);
}

#endif