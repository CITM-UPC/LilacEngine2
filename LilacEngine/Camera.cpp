#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp> // this is where we can find the function rotate, similar to the one we used last year in Physics

Camera::Camera() : fov(60), aspect(4.0/3.0), zNear(0.1), zFar(100), eye(0, 0, 0), center(0, 0, -1), up(0, 1, 0), yaw(-90) 
{
    WorldUp = up;
}

glm::dmat4 Camera::computeLookAt() const {
	return glm::lookAt(eye, center, up);
}

void Camera::cameraUpdate() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    center = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(center, WorldUp));
    up = glm::normalize(glm::cross(cameraRight, center));
}

void Camera::cameraMoveVertical(vec3 vector) {
	vec3 localZ = glm::normalize(eye - center);
	vec3 localY = glm::normalize(up);
	vec3 localX = glm::normalize(glm::cross(localY, localZ));

	vec3 localTranslation = glm::dmat3(localX, localY, localZ) * vector;

	center += localTranslation;
	eye += localTranslation;
}

void Camera::cameraMoveHorizontal(vec3 vector) {
	// Calculate local axes
	vec3 localZ = glm::normalize(eye - center);
	vec3 localY = glm::normalize(up);
	vec3 localX = glm::normalize(glm::cross(localY, localZ));

	// Separate translation along local X and local Z axes
	vec3 localTranslationX = localX * vector.x;
	vec3 localTranslationZ = localZ * vector.z;

	// Calculate the final translation vector
	vec3 localTranslation = localTranslationX + localTranslationZ;

	center += localTranslation;
	eye += localTranslation;
}

void Camera::cameraZoom(double amount) {
    double distanceToCenter = glm::distance(eye, center);
    vec3 localZ = glm::normalize(eye - center);

    eye += localZ * amount * (distanceToCenter * 0.1f);
}

void Camera::cameraOrbit(vec2 motion) {
	double sensibility = 0.005;

	if (motion.x != 0)
	{
		vec3 localZ = eye - center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.x) * sensibility), vec3(0, 1.0f, 0));

		eye = center + newLocalZ;
	}

	if (motion.y != 0)
	{
		vec3 localX;
		localX.x = computeLookAt()[0].x;
		localX.y = computeLookAt()[1].x;
		localX.z = computeLookAt()[2].x;

		vec3 localZ = eye - center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.y) * sensibility), localX);

		eye = center + newLocalZ;
	}
}