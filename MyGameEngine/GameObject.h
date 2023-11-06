#pragma once

#include "types.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture2D.h"

class GameObject {
public:
	GameObject();
	~GameObject();
	std::string name;
	
	Transform transform;
	Mesh mesh;
	Texture2D tex;

public:
	GameObject importGameObject(const std::string& path);
	std::vector<GameObject> getGameObject();
};