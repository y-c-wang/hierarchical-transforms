#include "camera.h"

Camera::Camera(
	glm::vec3 position,
	glm::vec3 worldUp,
	float yaw,
	float pitch,
	glm::vec3 front,
	float zoom
) : Position(position),
	Front(front),
	WorldUp(worldUp),
	Yaw(yaw),
	Pitch(pitch),
	Zoom(zoom)
{
	update();
}

glm::mat4 Camera::GetLookAt() {
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::update() {
	Front = glm::normalize(
		glm::vec3(
			cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
			sin(glm::radians(Pitch)),
			sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
		)
	);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}