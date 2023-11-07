#pragma once

#include "types.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Component.h"

#include <list>
#include <string>
#include <filesystem>
#include <fstream>
//#include <vector>


class GameObject {
public:
	std::string name;
	bool isActive = true;

private:

	std::shared_ptr<Component> GetComponent(Component::Type componentType);
	std::vector<std::shared_ptr<Component>> GetComponents();
	void AddComp(Component::Type component);
	void AddComp(std::shared_ptr<Mesh> component);
	void UpdateComponents();

	std::vector<std::shared_ptr<Component>> components;

public:
	GameObject();
	~GameObject();
	//std::string name;

	/*Transform transform;
	Mesh mesh;
	Texture2D tex;*/

};