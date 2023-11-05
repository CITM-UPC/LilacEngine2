#pragma once

#include "Cube.h"
#include <array>

class CubeVertexArray : public Cube
{
	std::array<vec3d, NUM_VERTEXS> _vertex_data;
	std::array<vec3d, NUM_VERTEXS> _color_data;

public:
	CubeVertexArray();
	void draw();
};

