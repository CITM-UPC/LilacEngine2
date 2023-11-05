#pragma once

#include "types.h"
#include "Graphic.h"

struct Cube : Graphic
{
	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	const vec3d a;
	const vec3d b;
	const vec3d c;
	const vec3d d;
	const vec3d e;
	const vec3d f;
	const vec3d g;
	const vec3d h;
			  
	const vec3d red;
	const vec3d green;
	const vec3d blue;
	const vec3d yellow;
	const vec3d white;
	const vec3d black;

	Cube();
};

