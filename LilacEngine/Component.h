#pragma once
#include <memory>
#include "GameObject.h"

enum class ComponentType 
{
	TRANSFORM, MESH, TEXTURE
};

class GameObject;

class Component {
public:
	//Component();
	//void Update();
	
	bool isActive = true;
	GameObject* gameObject;
	ComponentType componentType;
};
