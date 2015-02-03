#ifndef BOILERPLATE_TEXTURE_H
#define BOILERPLATE_TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../util/file.h"

class Texture{

public:
	Texture(const std::string filename);
	void Bind();
	void Unbind();
	virtual ~Texture();

protected:
	GLuint m_textureID;
	std::string m_path;
};

#endif