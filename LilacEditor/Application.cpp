#include "Application.h"
#include "Globals.h"
#include "Log.h"
#include "Window.h"
#include "Input.h"
#include "Hardware.h"
#include "UI.h"
#include "Renderer3D.h"

Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	LOG("Initializing Lilac Engine");
	engine = new EngineCore();

	window = new Window(this);
	input = new Input(this);
	hardware = new Hardware(this);
	ui = new UI(this);
	renderer = new Renderer3D(this);

	// Ordered for awake / Start / Update
	// Reverse order for CleanUp
	LOG("Initializing Modules");
	AddModule(window, true);
	AddModule(input, true);
	AddModule(hardware, true);
	AddModule(ui, true);

	// Render last to swap buffer
	AddModule(renderer, true);

	title = TITLE;
	organization = ORGANIZATION;
}

Application::~Application()
{
	// Release modules
	LOG("Releasing Modules");
	modules.clear();
}

void Application::AddModule(Module* module, bool activate)
{
	if (activate == true)
		module->Init();

	modules.push_back(module);
}

// Called before render is available
bool Application::Awake()
{
	bool ret = false;

	targetFrameDuration = (std::chrono::duration<double>)1 / targetFPS;

	//Load config from XML
	//ret = LoadConfig();
	ret = true;

	if (ret == true)
	{
		//title = configNode.child("app").child("title").child_value();

		//maxFrameDuration = configNode.child("app").child("frcap").attribute("value").as_int();

		for (const auto& item : modules)
		{
			if (item->active == false)
				continue;

			item->Awake();
		}
	}

	//LOG("---------------- Time Awake: %f/n", timer.ReadMSec());

	return ret;
}

// Called before the first frame
bool Application::Start()
{
	bool ret = true;

	dt = 0.016;

	for (const auto& item : modules)
	{
		if (item->active == false)
			continue;

		item->Start();
	}

	//LOG("----------------- Time Start(): %f", timer.ReadMSec());

	return ret;
}

// Called each loop iteration
bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();

	/*if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;*/

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}


// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameStart = std::chrono::steady_clock::now();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	frameEnd = std::chrono::steady_clock::now();
	auto frameDuration = std::chrono::duration_cast<std::chrono::duration<double>>(frameEnd - frameStart);

	//dt = frameDuration.count();

	if (frameDuration < targetFrameDuration)
	{
		std::chrono::duration<double> sleepTime = targetFrameDuration - frameDuration;
		std::this_thread::sleep_for(sleepTime);

		//dt = targetFrameDuration.count();
	}

	//// Update the fps Log
	//fps_log.push_back(app_framerate.prev_sec_frame_count);
	//if (fps_log.size() > 100)
	//	fps_log.erase(fps_log.begin());
}

// Call modules before each loop iteration
bool Application::PreUpdate()
{
	//OPTICK_CATEGORY("PreUpdate", Optick::Category::GameLogic);
	bool ret = true;

	for (const auto& item : modules)
	{
		if (item->active == false)
			continue;
		if (item->PreUpdate() == false)
			return false;
	}

	return ret;
}

// Call modules on each loop iteration
bool Application::DoUpdate()
{
	//OPTICK_CATEGORY("DoUpdate", Optick::Category::GameLogic);
	bool ret = true;

	for (const auto& item : modules)
	{
		if (item->active == false)
			continue;
		if (item->Update(dt) == false)
			return false;
	}

	return ret;
}

// Call modules after each loop iteration
bool Application::PostUpdate()
{
	//OPTICK_CATEGORY("PostUpdate", Optick::Category::GameLogic);
	bool ret = true;

	for (const auto& item : modules)
	{
		if (item->active == false)
			continue;
		if (item->PostUpdate() == false)
			return false;
	}

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	bool ret = true;

	for (auto item = modules.rbegin(); item != modules.rend(); ++item)
	{
		Module* module = *item;
		module->CleanUp();
	}

	return ret;
}

// 
int Application::GetArgc() const
{
	return argc;
}

// 
const char* Application::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

// Get App data
const char* Application::GetTitle()
{
	return title.c_str();
}

const char* Application::GetOrganization() 
{
	return organization.c_str();
}

void Application::SetTitle(string name) {
	title = name;
}

void Application::SetOrganization(string name) {
	organization = name;
}

// Get deltatime
float Application::GetDT()
{
	return dt;
}

void Application::AddLog(static char* log)
{
	logs.push_back(log);
}

vector<string> Application::GetLogs()
{
	return logs;
}

void Application::ClearLogs()
{
	logs.clear();
}