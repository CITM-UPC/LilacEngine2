#pragma once
#include <memory>

class GameObject;

class Component {
public:
	enum class Type {
		TRANSFORM, MESH, TEXTURE
	};

	bool isActve = true;

	GameObject* gameObject;

public:
	virtual void Update();
	virtual Type getType() const = 0;
};