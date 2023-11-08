#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "Component.h"
#include <memory>
#include <vector>
#include <GL\glew.h>

//using namespace std;

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

GameObject* GameObject::AddNewChildren() {
	std::string gameObjectName = name + " " + std::to_string(children.size());

	GameObject* tempGO = new GameObject(gameObjectName);
	AddChild(tempGO);
	return tempGO;
}

void GameObject::AddMeshWithTexture(std::vector<Mesh::Ptr> meshes) {
	if (meshes.size() == 1) {
		ComponentMesh* mesh = (ComponentMesh*)GetComponent(ComponentType::MESH);
		mesh->setMesh(*meshes.begin());
		ComponentTexture* texture = (ComponentTexture*)GetComponent(ComponentType::TEXTURE);
		texture->setTexture((*meshes.begin())->texture);
	}
	else {
		for (auto i = meshes.begin(); i != meshes.end(); ++i) {
			GameObject* GOPart = AddNewChildren();
			ComponentMesh* meshPart = (ComponentMesh*)GOPart->GetComponent(ComponentType::MESH);
			meshPart->setMesh(*i);
			ComponentTexture* texturePart = (ComponentTexture*)GOPart->GetComponent(ComponentType::TEXTURE);
			texturePart->setTexture((*i)->texture);
		}
	}
}

void GameObject::Render() {
	// get necessary components
	ComponentTransform* transform = (ComponentTransform*)GetComponent(ComponentType::TRANSFORM);
	ComponentMesh* mesh = (ComponentMesh*)GetComponent(ComponentType::MESH);

	// render
	glPushMatrix();
	glMultMatrixd(&transform->getTransform()[0].x);

	if (mesh->getMesh()) mesh->getMesh()->draw();

	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		(*childIt)->Render();
	}

	glPopMatrix();

}