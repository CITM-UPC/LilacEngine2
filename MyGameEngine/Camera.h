#pragma once

#include "types.h"

struct Camera
{
public:
	Camera();
	~Camera();
	mat4 computeLookAt() const;
	void cameraUpdate();

public:
	// Fov = field of view
	double fov;
	double aspect;
	double zNear;
	double zFar;

	// Position => eye
	// Target => center
	// Orientation => up
	vec3 eye; 
	vec3 center;
	vec3 up;
	vec3 direction;
	vec3 cameraRight;
	vec3 WorldUp;

	// Euler angles, yaw pitch roll
	double yaw, pitch;

	float zoom;
};

