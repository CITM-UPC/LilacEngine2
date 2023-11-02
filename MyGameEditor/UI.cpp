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
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(app->window->window, app->window->context);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	ImGui::StyleColorsDark();

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

bool UI::Update(double dt)
{
	bool ret = true;

	ImGuiIO& io = ImGui::GetIO();

#pragma region UI
	// For debugging
	//ImGui::ShowDemoWindow();

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

void UI::showMenu() {

}

void UI::showConsole() {

}

void UI::showConfiguration() {
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("Configuration");
	if (ImGui::CollapsingHeader("Application")) {
		//	// --- Organization name ---
		//	static char orgName[100];
		//	if (App->GetOrganizationName() != nullptr)
		//		strcpy_s(orgName, 100, App->GetOrganizationName());
		//	if (ImGui::InputText("Organization Name", orgName, 100, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
		//		App->SetOrganizationName(orgName);

		//	ImGui::Separator();
		//	// --- Cap frames ---
			//int maxFramerate = App->time->GetMaxFramerate();
			//if (ImGui::SliderInt("Max FPS", &maxFramerate, 0, App->window->GetDisplayRefreshRate()))
			//	App->time->SetMaxFramerate(maxFramerate);

		char title[25];
		//sprintf_s(title, 25, "Framerate %.1f", FPS_Tracker[FPS_Tracker.size() - 1]);
		//ImGui::PlotHistogram("##Framerate", &FPS_Tracker[0], FPS_Tracker.size(), 0, title, 0.0f, 100.0f, ImVec2(500, 75));
		//sprintf_s(title, 25, "Milliseconds %0.1f", MS_Tracker[MS_Tracker.size() - 1]);
		//ImGui::PlotHistogram("##Milliseconds", &MS_Tracker[0], MS_Tracker.size(), 0, title, 0.0f, 40.0f, ImVec2(500, 75));

	//	sMStats MemoryStats = m_getMemoryStatistics(); // Using mmgr 
	//	static int speed = 0;
	//	static std::vector<float> Memory(100); // Hom many units/lines we want in the plot
	//	if (++speed > 25) // How fast the plot is plotted :)
	//	{
	//		speed = 0;
	//		if (Memory.size() == 100)
	//		{
	//			for (uint i = 0; i < 100 - 1; ++i)
	//				Memory[i] = Memory[i + 1];

	//			Memory[100 - 1] = (float)MemoryStats.totalReportedMemory;
	//		}
	//		else
	//			Memory.push_back((float)MemoryStats.totalReportedMemory);
	//	}

	//	ImGui::PlotHistogram("##Memory", &Memory[0], Memory.size(), 0, "Memory Consumption", 0.0f, (float)MemoryStats.peakReportedMemory * 1.2f, ImVec2(500, 75));

	//	ImGui::Text("Total Reported Memory: %u", MemoryStats.totalReportedMemory);
	//	ImGui::Text("Total Actual Memory: %u", MemoryStats.totalActualMemory);
	//	ImGui::Text("Peak Reported Memory: %u", MemoryStats.peakReportedMemory);
	//	ImGui::Text("Peak Actual Memory: %u", MemoryStats.peakActualMemory);
	//	ImGui::Text("Accumulated Reported Memory: %u", MemoryStats.accumulatedReportedMemory);
	//	ImGui::Text("Accumulated Actual Memory: %u", MemoryStats.accumulatedActualMemory);
	//	ImGui::Text("Accumulated Alloc Unit Count: %u", MemoryStats.accumulatedAllocUnitCount);
	//	ImGui::Text("Total Alloc Unit Count: %u", MemoryStats.totalAllocUnitCount);
	//	ImGui::Text("Peak Alloc Unit Count: %u", MemoryStats.peakAllocUnitCount);
	}
	if (ImGui::CollapsingHeader("Window")) {
		if (ImGui::SliderFloat("Brightness", &v, 0.0, 1.0))
			app->window->SetWindowBrightness(v);
		if (ImGui::Checkbox("Fullscreen", &fullscreen))
			app->window->SetFullscreen(fullscreen);
		if (ImGui::Checkbox("Resizable", &resizable))
			app->window->SetResizable(resizable);
		if (ImGui::Checkbox("Borderless", &borderless))
			app->window->SetBorderless(!borderless);
		if (ImGui::Checkbox("Fullscreen Desktop", &fullDesktop))
			app->window->SetFullDesktop(!fullDesktop);
	}
	if (ImGui::CollapsingHeader("Renderer")) {
		if (ImGui::Checkbox("Vsync", &vsync))
			app->renderer->SetVsync(vsync);
	}
	if (ImGui::CollapsingHeader("Input")) {
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
		ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
	}
	if (ImGui::CollapsingHeader("Audio")) {
		ImGui::Text("No audio applied for now!", io.MousePos.x, io.MousePos.y);
		//if (ImGui::SliderFloat("Music", &v, 0.0, 1.0))
		//
		//if (ImGui::SliderFloat("Fx", &v, 0.0, 1.0))
		//
	}
	if (ImGui::CollapsingHeader("Textures")) {

	}
	if (ImGui::CollapsingHeader("Hardware")) {

	}
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showHierarchy() {
	ImGui::Begin("Hierarchy");
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showInspector() {
	ImGui::Begin("Inspector");
	//if () {
	if (ImGui::TreeNode("Transform")) {
		ImGui::SeparatorText("Position");
		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::SeparatorText("Rotate");
		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::SeparatorText("Scale");
		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Mesh")) {
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Texture")) {
		ImGui::TreePop();
	}
	ImGui::EndMenu();
	ImGui::End();
	//}
}

void UI::showLoad() {
	ImGui::Begin("Load");
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showAbout() {
	ImGui::OpenPopup("About");
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Lilac Engine");
		ImGui::Text("An engine in development");
		ImGui::Text("by Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
		ImGui::Text("3rd Party Libraries used:");
		// Need to change this
		ImGui::Text("- SDL 2");
		ImGui::Text("- ImGui\n\n");
		ImGui::Text("License:\n\n");
		ImGui::Text("MIT License\n\n");
		// 1st Paragraph
		ImGui::Text("Copyright (c) 2023 Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
		ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy\n");
		ImGui::Text("of this software and associated documentation files (\"the Software\"), to deal\n");
		ImGui::Text("in the Software without restriction, including without limitation the rights\n");
		ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n");
		ImGui::Text("copies of the Software, and to permit persons to whom the Software is\n");
		ImGui::Text("furnished to do so, subject to the following conditions : \n\n");
		// 2nd Paragraph
		ImGui::Text("The above copyright notice and this permission notice shall be included in all\n");
		ImGui::Text("copies or substantial portions of the Software.\n\n");
		// 3rd
		ImGui::Text("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
		ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n");
		ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n");
		ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n");
		ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n");
		ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n");
		ImGui::Text("SOFTWARE\n\n");

		if (ImGui::Button("Close the window")) {
			about = !about;
		}
		ImGui::EndPopup();
	}
}

void UI::showGame() {
	ImGui::Begin("GameWindow");
	{
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("GameRender");
		// Get the size of the child (i.e. the whole draw size of the windows).
		ImVec2 wsize = ImGui::GetWindowSize();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		//ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}
	ImGui::End();
}

void UI::calculateFramerate() {

}