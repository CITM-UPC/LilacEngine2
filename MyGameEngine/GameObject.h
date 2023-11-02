#pragma once

#include "types.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture2D.h"

class GameObject {
	GameObject();
	~GameObject();
	std::string name;
	
	Transform transform;
	Mesh mesh;
	Texture2D tex;

};