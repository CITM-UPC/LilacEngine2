#ifndef __UI_H__
#pragma once

#include "Globals.h"
#include "Module.h"
#include "Hardware.h"
#include "..\LilacEngine\GameObject.h"

class UI : public Module
{
public:
	UI(Application* app);
	~UI();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(double dt);
	bool PostUpdate();
	bool CleanUp();
	void HandleInput(SDL_Event* event);
	void RenderUI();

	// JULS: Temporal functions, this will be moved into files 
	void showMenu();
	void showConsole();
	void showConfiguration(HardwareInfo hardware_info);
	void showHierarchy();
	void writeHierarchy(GameObject* gameObject);
	void showInspector(GameObject* selected);
	void showInspectorTransform(Component* component);
	void showInspectorMesh(Component* component);
	void showInspectorTexture(Component* component);
	void showResources();
	void showAbout(HardwareInfo hardware_info);
	void showGame();
	void showHardwareInfo(HardwareInfo hardware_info);	
	void calculateFramerate();
	
	GameObject* selected;
private:
	//// General
	bool console = true, configuration = true, hierarchy = true, inspector = true, shapes = true, menu = true, quit = false;
	
	//// Console

	//// Configuration
	// Framegraph
	char title[25];
	float frame_rate;
	float milliseconds;

	std::vector<float> frame_list;
	std::vector<float> ms_list;

	// Booleans to activate menus that are not shown
	// about -> Information about the engine
	// showcase -> Imgui Demo window
	bool about = false;

	// Booleans to change the properties of our window
	float v = 1.0;
	bool fullscreen, resizable, borderless, fullDesktop;

	// Bool to set Vsync
	bool vsync;

	//// Hierarchy
	

	//// Inspector
	//void setCheckersTexture();

	bool triangles, faces, checkers;

	//// Shapes

};

#endif // !__UI_H__