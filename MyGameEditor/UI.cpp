#include "Application.h"
#include "Globals.h"
#include "UI.h"
#include "Log.h"
#include "Window.h"

UI::UI(Application* app) : Module(app)
{

}

UI::~UI() {

}

bool UI::Awake()
{
	bool ret = true;

	return ret;
}

bool UI::Start()
{
	bool ret = true;

	LOG("Init SDL ImGui event system");

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	//Enable
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();

	return ret;
}

bool UI::PreUpdate()
{
	bool ret = true;

	// (After event loop)
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	return ret;
}

bool UI::Update(float dt)
{
	bool ret = true;

	ImGuiIO& io = ImGui::GetIO();

#pragma region UI
	// For debugging
	ImGui::ShowDemoWindow();

	// Tabs
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("General")) {
		if (ImGui::BeginMenu("Editor")) {
			if (ImGui::MenuItem("Console"))
				console = !console;
			if (ImGui::MenuItem("Configuration"))
				configuration = !configuration;
			if (ImGui::MenuItem("Hierarchy"))
				hierarchy = !hierarchy;
			if (ImGui::MenuItem("Inspector"))
				inspector = !inspector;
			if (ImGui::MenuItem("Shapes"))
				shapes = !shapes;
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Github page")) {
			ShellExecute(0, 0, "https://github.com/CITM-UPC/LilacEngine", 0, 0, SW_SHOW);
		}
		if (ImGui::MenuItem("About")) {
			about = !about;
		}
		if (ImGui::MenuItem("Quit")) {
			return false;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	// About tab
	if (about)
		showAbout();
	if (console)
		showConsole();
	if (configuration)
		showConfiguration();
	if (hierarchy)
		showHierarchy();
	if (inspector)
		showInspector();
	if (shapes)
		showLoad();

	showGame();

	return ret;
}

bool UI::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool UI::CleanUp()
{
	bool ret = true;

	LOG("Cleaning up IMGUI");
	bool ret = true;

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return ret;
}

void UI::HandleInput(SDL_Event* event) {
	ImGui_ImplSDL2_ProcessEvent(event);
}

void UI::RenderUI() {
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}