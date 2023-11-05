#include "Camera.h"
#include "types.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()  //:fov(60), aspect(4.0/3.0), zNear(0.1), zFar(100), eye(0, 0, 0), center(0, 0, -1), up(0, 1, 0), yaw(-90) 
{
    CalculateViewMatrix();

    X = vec3d(1.0f, 0.0f, 0.0f);
    Y = vec3d(0.0f, 1.0f, 0.0f);
    Z = vec3d(0.0f, 0.0f, 1.0f);

    Position = vec3d(0.0f, 0.0f, 5.0f);
    Reference = vec3d(0.0f, 0.0f, 0.0f);
    //WorldUp = up;
}

void Camera::Look(const vec3d& Position, const vec3d& Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3d(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += (Z.x * (0.05f), Z.y * (0.05f), Z.z * (0.05f));
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera::LookAt(const vec3d& Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3d(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera::Move(const vec3d& Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

vec3d Camera::Rotate( vec3d& u, float angle,  vec3d& v) {
	//First rotation => angle and vector v
	
	angle = angle / 180.0f * (float)M_PI;
	//float c = cos(angle), s = sin(angle);
	//
	//vec3d rot((vec3d)(v.x * c - v.y * s, v.x * s + v.y * c));


	mat4d rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, (v);

	//return *(rot * vec4d(u, 1.0f));
}

// -----------------------------------------------------------------
float* Camera::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

//glm::dmat4 Camera::computeLookAt() const {
//	return glm::lookAt(eye, center, up);
//}
//
//void Camera::cameraUpdate() {
//    glm::vec3 direction;
//    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    direction.y = sin(glm::radians(pitch));
//    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    center = glm::normalize(direction);
//    cameraRight = glm::normalize(glm::cross(center, WorldUp));
//    up = glm::normalize(glm::cross(cameraRight, center));
//}