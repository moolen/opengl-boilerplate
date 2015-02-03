#ifndef BOILERPLATE_CAMERA_CPP
#define BOILERPLATE_CAMERA_CPP

#include "camera.h"
#include <glm/ext.hpp>
#include <iostream>

Camera::Camera(
	const glm::vec3& pos,
	float fov,
	float aspect,
	float zNear,
	float zFar
)
{
	m_pos = pos;

	m_forward = glm::vec3(
		0.0f,
		0.0f,
		-100.0f
	);

	m_up = glm::vec3(
		0.0f,
		1.0f,
		0.0f
	);
	
	m_projection = glm::perspective(
		fov,
		aspect,
		zNear,
		zFar
	);

	m_view = glm::lookAt(
        m_pos,
        m_pos + m_forward,
        m_up
	);

}

glm::mat4 Camera::GetProjection(){
	return m_projection;
}

glm::mat4 Camera::GetView(){
    return m_view;;
}

void Camera::Update(){
	m_view = glm::lookAt(
    	m_pos,
        m_pos + m_forward,
        m_up
    );
}

float* Camera::GetProjectionPtr(){
	return &m_projection[0][0];
}

float* Camera::GetViewPtr(){
	return &m_view[0][0];
}

void Camera::MoveForward(float amount){
	m_pos += m_forward * amount;
	Update();
}

void Camera::MoveBackward(float amount){
	m_pos -= m_forward * amount;
	Update();
}

void Camera::MoveLeft(float amount){
	m_pos += glm::cross(m_up, m_forward) * amount;
	Update();
}

void Camera::MoveRight(float amount){
	m_pos -= glm::cross(m_up, m_forward) * amount;
	Update();
}

void Camera::Pitch(float angle)
{
	angle = angle * INVERT_Y_AXIS_MULTIPLIER * PITCH_SPEED;
	glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

	m_forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_forward, 0.0)));
	m_up = glm::normalize(glm::cross(m_forward, right));
	Update();
}

void Camera::Rotate(float angle)
{
	angle = angle * ROTATE_SPEED;
	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(angle, UP);

	m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
	m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
	Update();
}

glm::vec3 Camera::GetForward(){
	return m_forward;
}


#endif