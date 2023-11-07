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
	/*std::shared_ptr<Component> newComponent;

	switch (component) {
	case Component::Type::MESH:
		newComponent = std::make_shared<Mesh>();
		break;
	case Component::Type::TRANSFORM:
		newComponent = std::make_shared<Transform>();
		break;
	case Component::Type::TEXTURE:
		newComponent = std::make_shared<Texture2D>();
		break;
	}

	components.push_back(newComponent);*/
}

void GameObject::AddComponent(std::shared_ptr<Mesh> component)
{
	//components.push_back(component);
}

void GameObject::UpdateComponents()
{
	for (auto& comp : components)
	{
		comp->Update();
	}
}

