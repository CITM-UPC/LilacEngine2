#pragma once

#include "types.h"

struct Camera
{
	// Fov = field of view
	double fov;
	double aspect;
	double zNear;
	double zFar;

	vec3 eye;
	vec3 center;
	vec3 up;

	mat4 computeLookAt() const;

	Camera();

	// For input
	float speed;
	void cameraOrbit();
	void cameraFocus();
};

