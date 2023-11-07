#ifndef __APP_H__
#define __APP_H__
#pragma once

#include "Globals.h"
#include "Module.h"
#include "Log.h"
#include "..\LilacEngine\EngineCore.h"

class Window;
class Input;
class Hardware;
class UI;
class Renderer3D;

class Application
{
public:
	// Constructor
	Application(int argc, char* args[]);

	// Destructor
	virtual ~Application();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module, bool activate);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;

	// App information
	const char* GetTitle();
	const char* GetOrganization();
	void SetTitle(string name);
	void SetOrganization(string name);

	// Dt
	float GetDT();

	// Logs
	void AddLog(static char* log);
	vector<string> GetLogs();
	void ClearLogs();

private:
	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	vector<string> logs;

public:
	EngineCore* engine;
	
	// Modules
	Window* window;
	Input* input;
	Hardware* hardware;
	UI* ui;
	Renderer3D* renderer;

	int musicValue = 100;
	int sfxValue = 100;

	// Graphs ImGui
	std::vector<float> fps_log;
	std::vector<float> ms_log;

private:
	int argc;
	char** args;
	string title;
	string organization;

	list<Module*> modules;

	// Fps control
	double targetFPS = 60;
	std::chrono::duration<double> targetFrameDuration;
	std::chrono::steady_clock::time_point frameStart, frameEnd;
	double dt;
};

extern Application* app;

#endif	// !__APP_H__