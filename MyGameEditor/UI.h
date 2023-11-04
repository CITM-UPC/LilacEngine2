#ifndef __UI_H__
#pragma once

#include "Globals.h"
#include "Module.h"
#include "Hardware.h"

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
	void showConfiguration();
	void showHierarchy();
	void showInspector();
	void showLoad();
	void showAbout();
	void showGame();
	void calculateFramerate();
	void showHardwareInfo();
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
	float f = 12.0;

	//// Shapes

};

#endif // !__UI_H__