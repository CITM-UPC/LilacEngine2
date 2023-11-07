#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "Component.h"
#include <memory>
#include <vector>

using namespace std;

GameObject::GameObject() 
{
	name = "";
	AddComponent(ComponentType::TRANSFORM);
	AddComponent(ComponentType::MESH);
	AddComponent(ComponentType::TEXTURE);
}

GameObject::GameObject(std::string name) {
	this->name = name;
	AddComponent(ComponentType::TRANSFORM);
	AddComponent(ComponentType::MESH);
	AddComponent(ComponentType::TEXTURE);
}

GameObject::~GameObject() {} 

Component* GameObject::GetComponent(ComponentType componentType)
{
	for (auto i = components.begin(); i != components.end(); ++i) {
		if ((*i)->componentType == componentType) {
			return *i;
		}
	}
	return nullptr;
}

std::list<Component*> GameObject::GetComponents()
{
	return components;
}

void GameObject::AddComponent(ComponentType componentType) {
	Component* newComponent = nullptr;

	switch (componentType) {
	case ComponentType::TRANSFORM:
		newComponent = new ComponentTransform();
		break;	
	case ComponentType::MESH:
		newComponent = new ComponentMesh();
		break;
	case ComponentType::TEXTURE:
		newComponent = new ComponentTexture();
		break;
	}

	components.push_back(newComponent);
}

void GameObject::AddChild(GameObject* child) {
	if (child->_parent == this) return;
	if (child->_parent) child->_parent->RemoveChild(child);
	children.push_back(child);
	child->_parent = this;
}

void GameObject::RemoveChild(GameObject* child) {
	children.remove(child);
	child->_parent = nullptr;
}