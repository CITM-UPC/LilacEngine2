#pragma once

#include "types.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture2D.h"

struct Components {
	Transform transform;
	Mesh mesh;
	Texture2D tex;
};

class GameObject {
public:
	GameObject();
	~GameObject();


public:
	std::string name;
	Components components;
};