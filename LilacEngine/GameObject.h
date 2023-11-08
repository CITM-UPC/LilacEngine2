#pragma once

#include "types.h"
#include "Component.h"
#include <string>
#include <list>
#include "Mesh.h"
#include "Texture2D.h"

class Component;

class GameObject {
public:
	GameObject();
	GameObject(std::string name);
	
	~GameObject();
	std::string name;
	bool isActive = true;
	std::string defaultTexture;

	// Components
	Component* GetComponent(ComponentType componentType);
	std::list<Component*> GetComponents();
	void AddComponent(ComponentType componentType);
	//void UpdateComponents();

	std::list<Component*> components;

	// Child
	GameObject* _parent;
	std::list<GameObject*> children;
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	GameObject* AddNewChildren();


	void AddMeshWithTexture(std::vector<Mesh::Ptr> meshes);
	//void changeTexture(GameObject* GO, std::string path);
	void Render();
};