#pragma once
#include <memory>
#include "GameObject.h"

class GameObject;

class Component {
public:
	enum class Type {
		TRANSFORM, MESH, TEXTURE
	};

	bool isActve = true;
	GameObject* gameObject;

public:
	Component();
	virtual void Update();
	virtual Type getType() const = 0;
};
