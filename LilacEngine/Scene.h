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
		//int num = 0;
		//for (auto gameObject = children.begin(); gameObject != children.end(); ++gameObject) {
		//	if ((*gameObject)->name == tempGO->name) {
		//		num++;
		//	}
		//}
		//tempGO->se = name + " " + std::to_string(num);
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
		for (auto gameObject = children.begin(); gameObject != children.end(); ++gameObject) {
			if ((*gameObject)->isActive) {
				(*gameObject)->Render();
			}

		}

	};

	void CleanUp() {};

	// uuid id
	std::string name;
	// should be a list of uuids
	std::list<GameObject*> children;
};