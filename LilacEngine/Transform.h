#pragma once

#include "types.h"

class Transform {
public:
	enum class Space
	{
		LOCAL,
		GLOBAL,
	};

	Transform();
	~Transform();

	void MoveTo(vec3 position, Space referenceFrame = Space::GLOBAL);
	void Move(vec3 displacement, Space referenceFrame = Space::LOCAL);
	void RotateTo(vec3f axis);
	void Rotate(vec3f axis, Space referenceFrame = Space::LOCAL);
	void Update();


	
	
	
private:
	vec3 pos;
	vec3 scale;
	vec4 rotation;
};