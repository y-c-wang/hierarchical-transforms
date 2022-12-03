#pragma once
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 INIT_CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 INIT_CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 INIT_CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const float INIT_CAMERA_YAW = -90.0f;
const float INIT_CAMERA_PITCH = 0.0f;
const float INIT_CAMERA_ZOOM = 90.0f;

class Camera
{
private:
	void update();
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float Zoom;

	Camera(
		glm::vec3 position = INIT_CAMERA_POSITION,
		glm::vec3 worldUp = INIT_CAMERA_UP,
		float yaw = INIT_CAMERA_YAW,
		float pitch = INIT_CAMERA_PITCH,
		glm::vec3 front = INIT_CAMERA_FRONT,
		float zoom = INIT_CAMERA_ZOOM
	);

	glm::mat4 GetLookAt();
};