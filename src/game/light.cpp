#ifndef BOILERPLATE_LIGHT_CPP
#define BOILERPLATE_LIGHT_CPP

#include "light.h"

/**
 * constructor
 */
Light::Light(glm::vec3 position, glm::vec3 color):
	m_position(position),
	m_color(color)
{}

/**
 * 
 * getter & setter
 *
 */
void Light::SetPosition(glm::vec3 position){
	m_position = position;
}

float* Light::GetPosition(){
	return glm::value_ptr(m_position);

}

void Light::SetColor(glm::vec3 color){
	m_color = color;
}

float* Light::GetColor(){
	return glm::value_ptr(m_color);
}


/**
 * destructor
 */
Light::~Light(){

}

#endif