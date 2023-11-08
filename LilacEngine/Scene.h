#pragma once
#include <string>
#include <list>
#include "GameObject.h"

class Scene {
public:
	Scene() {

	};
	Scene(std::string name) {
		this->name = name;
	};
	~Scene() {

	};

	GameObject* AddGameObject(std::string name) {
		GameObject* tempGO = new GameObject(name);
		children.push_back(tempGO);
		return tempGO;
	}

	GameObject* AddGameObject() {
		std::string gameObjectName = "Game Object " + std::to_string(children.size());

		GameObject* tempGO = new GameObject(gameObjectName);
		children.push_back(tempGO);
		return tempGO;
	}

	GameObject* AddGameObjectChildren(GameObject* parent) {
		std::string gameObjectName = parent->name + " " + std::to_string(parent->children.size());

		GameObject* tempGO = new GameObject(gameObjectName);
		parent->AddChild(tempGO);
		return tempGO;

	}

	void DebugStart() {
		{
			AddGameObject();
		}
		{
			GameObject* temp = AddGameObject();
			AddGameObjectChildren(temp);
		}
		{
			AddGameObject();
		}
	};

	void Start() {};

	void Update() {};

	void Render() {
		for (auto gameObjectI = children.begin(); gameObjectI != children.end(); ++gameObjectI) {
			(*gameObjectI)->Render();
		}

	};

	void CleanUp() {};

	// uuid id
	std::string name;
	// should be a list of uuids
	std::list<GameObject*> children;
};