#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__
#pragma once

// Include in Editor when needed: #include "../TheOneEngine/EngineCore.h"
#include "Camera.h"
//#include "Texture2D.h"
#include "Scene.h"
class EngineCore
{
public:

	enum class RenderModes { RELEASE, DEBUG };

	EngineCore();

	void Awake();
	void Start();

	void Update(double dt);

	void Render(RenderModes renderMode);

public:
	Camera camera;
	//Scene scene;

};

#endif // !__ENGINE_CORE_H__