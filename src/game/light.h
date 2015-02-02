#ifndef BOILERPLATE_LIGHT_H
#define BOILERPLATE_LIGHT_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Light{

public:
	Light(glm::vec3 position, glm::vec3 color);

	void SetPosition(glm::vec3 position);
	void SetColor(glm::vec3 color);
	float* GetPosition();
	float* GetColor();


	virtual ~Light();

protected:
	glm::vec3 m_position;
	glm::vec3 m_color;

};

#endif