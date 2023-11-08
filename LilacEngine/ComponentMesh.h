#pragma once

#include "types.h"
#include "Component.h"

class Component;

class ComponentMesh : public Component {
public:
	ComponentMesh() {
		componentType = ComponentType::MESH;
	}

	~ComponentMesh() {}

	void setMesh(Mesh::Ptr mesh) {
		_mesh = mesh;
	}

	Mesh::Ptr getMesh() {
		return _mesh;
	}

private:
	Mesh::Ptr _mesh = nullptr;
};