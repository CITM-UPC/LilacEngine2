#include "GameObject.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Transform.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

using namespace std;
namespace fs = filesystem;

GameObject::GameObject() {

	name = "";
	//components.push_back(std::make_shared<Transform>());
}

GameObject::~GameObject() {} 

std::shared_ptr<Component> GameObject::GetComponent(Component::Type componentType)
{
	for (auto& comp : components)
	{
		if (comp->getType() == componentType)
		{
			return comp;
		}
	}

	return nullptr;
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents()
{
	return components;
}

void GameObject::AddComponent(Component::Type component) {
	Component* newComponent = nullptr;

	/*switch(component) {
	case Component::Type::MESH:
		newComponent = Mesh();
		break;
	case Component::Type::TRANSFORM:
		newComponent = Transform();
		break;
	case Component::Type::TEXTURE:
		newComponent = Texture2D();
		break;
	}

	components.push_back(newComponent);*/
}

void GameObject::AddComponent(std::shared_ptr<Mesh> component)
{
	//components.push_back(component);
}

void GameObject::RemoveComponent(Component::Type component)
{
	for (auto& comp : components)
	{
		if (comp->getType() == component)
		{
			components.erase(std::remove(components.begin(), components.end(), comp));
			break;
		}
	}
}

GameObject* GameObject::Find(std::string name, std::list<GameObject> gameObjectList)
{
	for (auto& go : gameObjectList)
	{
		if (go.name == name)
		{
			return &go;
		}
	}
	return nullptr;
}

void GameObject::UpdateComponents()
{
	for (auto& comp : components)
	{
		comp->Update();
	}
}

void GameObject::Rename(std::string Rename, std::list<GameObject> gameObjectList) {

	for (auto& go : gameObjectList)
	{
		Rename = name;
	}
}
