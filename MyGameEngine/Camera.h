#pragma once

#include "types.h"
#include "glmath.h"

struct Camera
{
public:
	Camera();
	~Camera();
	//mat4 computeLookAt() const;
	//void cameraUpdate();

	void Look(const vec3d& Position, const vec3d& Reference, bool RotateAroundReference = false);
	void LookAt(const vec3d& Spot);
	void Move(const vec3d& Movement);
	vec3d Rotate(vec3d& u, float angle, vec3d& v);
	//vec3 Rotate2VectorsFloat(const vec3& u, float angle, const vec3& v);
	//mat4x4 RotationMatrix(float angle, const vec3& u);
	float* GetViewMatrix();
	void CalculateViewMatrix();

public:
	vec3d X, Y, Z, Position, Reference;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;

	// JULS: Changing the camara to the one used in Physics bc it is easier to understand
	//// Fov = field of view
	//double fov;
	//double aspect;
	//double zNear;
	//double zFar;
	//
	//// Position => eye
	//// Target => center
	//// Orientation => up
	//vec3 eye; 
	//vec3 center;
	//vec3 up;
	//vec3 direction;
	//vec3 cameraRight;
	//vec3 WorldUp;
	//
	//// Euler angles, yaw pitch roll
	//double yaw, pitch;
	//
	//float zoom;
};

