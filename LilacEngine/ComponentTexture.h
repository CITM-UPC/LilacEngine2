#pragma once

#include "types.h"
#include "Component.h"

class Component;

class ComponentTexture : public Component {
public:
	ComponentTexture() {
		componentType = ComponentType::TEXTURE;
	}
	 ~ComponentTexture() {}

	void setTexture(Texture2D::Ptr texture) {
		_texture = texture;
	}

	Texture2D::Ptr getTexture() {
		return _texture;
	}

private:
	Texture2D::Ptr _texture = nullptr;
};