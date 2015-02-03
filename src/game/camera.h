#ifndef BOILERPLATE_CAMERA_H
#define BOILERPLATE_CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class Camera{

public:
	Camera(
		const glm::vec3& pos,
		float fov,
		float aspect,
		float zNear,
		float zFar
	);

	glm::mat4 GetProjection();
	glm::mat4 GetView();
	float* GetProjectionPtr();
	float* GetViewPtr();
	glm::vec3 GetForward();
	void Update();

	void MoveForward(float amount);
	void MoveBackward(float amount);
	void MoveLeft(float amount);
	void MoveRight(float amount);

	void Pitch(float angle);
	void Rotate(float angle);

protected:

	const double MOVE_SPEED = 0.3f;
	const double ROTATE_SPEED = 0.03f;
	const double PITCH_SPEED = 0.03f;
	const double INVERT_Y_AXIS_MULTIPLIER = -1;

	glm::mat4 m_projection;
	glm::mat4 m_view;

	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;


};

#endif