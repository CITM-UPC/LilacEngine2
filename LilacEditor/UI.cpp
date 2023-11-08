#include "Application.h"
#include "Globals.h"
#include "UI.h"
#include "Log.h"
#include "Window.h"
#include "Renderer3D.h"
#include "..\LilacEngine\Scene.h"
#include "..\LilacEngine\ComponentTransform.h"
#include "..\LilacEngine\ComponentMesh.h"
#include "..\LilacEngine\ComponentTexture.h"

UI::UI(Application* app) : Module(app)
{

}

UI::~UI() {

}

bool UI::Awake()
{
	bool ret = true;
	quit = false;

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
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport / Platform Windows

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(app->window->window, app->window->context);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// JULS: COLORS IMGUI REMINDER => Values go from 0 - 1, not from 0 - 225
	ImGui::StyleColorsDark();
	selected = NULL;
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
	HardwareInfo hardware_info = app->hardware->GetInfo();

#pragma region UI
	// For debugging
	//ImGui::ShowDemoWindow();

	// About tab
	if (about)
		showAbout(hardware_info);
	if (console)
		showConsole();
	if (configuration)
		showConfiguration(hardware_info);
	if (hierarchy)
		showHierarchy();
	if (inspector)
		showInspector(selected);
	if (shapes)
		showResources();
	if (menu)
		showMenu();
	if (quit)
		return false;
	//showGame();

#pragma endregion

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
			LOG("Opening Github page!");
			ShellExecute(0, 0, "https://github.com/CITM-UPC/LilacEngine2", 0, 0, SW_SHOW);
		}
		if (ImGui::MenuItem("About")) {
			about = !about;
		}
		if (ImGui::MenuItem("Quit")) {
			quit = true;
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Load")) {
		if (ImGui::MenuItem("Cube")) {
			LOG("Adding Cube to the scene");
		}
		if (ImGui::MenuItem("Sphere")) {
			LOG("Adding Sphere to the scene");
		}
		if (ImGui::MenuItem("Teapot")) {
			LOG("Adding Teapot to the scene");
			GameObject* teapot = app->engine->scene->AddGameObject("Teapot");
			auto mesh_ptrs = Mesh::loadFromFile("Assets\\teapot.fbx", "Assets\\checkers1.png");
			teapot->AddMeshWithTexture(mesh_ptrs);

			ComponentMesh* meshComp = (ComponentMesh*)teapot->GetComponent(ComponentType::MESH);

			ComponentTransform* meshtransform = (ComponentTransform*)teapot->GetComponent(ComponentType::TRANSFORM);
			meshtransform->rotate(0, vec3(0, 1, 0));
			meshtransform->translate(vec3(5, 0, 0));
			meshtransform->scale(vec3(1, 1, 1));
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void UI::showConsole() {
	ImGuiWindowFlags consoleFlags = 0;
	consoleFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

	if (ImGui::Begin("Console"))
	{
		if (ImGui::SmallButton("Clear"))
			app->ClearLogs();
		
		ImGui::Separator();
	
		ImGuiWindowFlags scrollFlags = 0;
		scrollFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		scrollFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
	
		if (ImGui::BeginChild("Scrollbar", ImVec2(0, 0), false, scrollFlags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 1));
			for (const auto& log : app->GetLogs())
			{
				ImGui::TextUnformatted(log.data());
				ImGui::PopStyleColor();
			}
		
			ImGui::PopStyleVar();
		
			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);
		
			ImGui::EndChild();
		}
		ImGui::EndMenu();
		ImGui::End();
	}
}

void UI::showConfiguration(HardwareInfo hardware_info) {
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("Configuration");
	if (ImGui::CollapsingHeader("Application")) {
		// Title
		static char titleName[100];
		ImGui::Text("Name:");
		if (app->GetTitle() != nullptr)
			strcpy_s(titleName, 100, app->GetTitle());
		if (ImGui::InputText("", titleName, 100, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			app->SetOrganization(titleName);
		
		// Organization name
		static char orgName[100];
		ImGui::Text("Name:");
		if (app->GetOrganization() != nullptr)
			strcpy_s(orgName, 100, app->GetOrganization());
		if (ImGui::InputText("", orgName, 100, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			app->SetOrganization(orgName);
		
		// FPS Graph
		calculateFramerate();
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
		ImGui::Text("No audio applied for now!");
		//if (ImGui::SliderFloat("Music", &v, 0.0, 1.0))
		//
		//if (ImGui::SliderFloat("Fx", &v, 0.0, 1.0))
		//
	}
	if (ImGui::CollapsingHeader("Textures")) {

	}
	if (ImGui::CollapsingHeader("Hardware")) {
		//JULS: problems with hardware, debugging
		showHardwareInfo(hardware_info);
	}
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showHierarchy() {
	
	ImGui::Begin("Hierarchy");
	if (app->engine->scene != nullptr) {
		Scene* sceneToUI = app->engine->scene;
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::CollapsingHeader(sceneToUI->name.c_str())) {
			for (std::list<GameObject*>::iterator it = sceneToUI->children.begin(); it != sceneToUI->children.end(); ++it) {
				writeHierarchy(*it);
			}
		}
	}
	ImGui::EndMenu();
	ImGui::End();
}

void UI::writeHierarchy(GameObject* gameObject) {
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (gameObject->children.empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}
	if (selected != NULL && selected == gameObject) {
		flags |= ImGuiTreeNodeFlags_Selected;
	}

	bool nodeIsOpen = ImGui::TreeNodeEx(gameObject->name.c_str(), flags);

	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
		selected = gameObject;
	}

	//if (ImGui::Tre)
	if (nodeIsOpen) {
		for (std::list<GameObject*>::iterator it = gameObject->children.begin(); it != gameObject->children.end(); ++it) {
			writeHierarchy(*it);
		}
		ImGui::TreePop();
	}
}

void UI::showInspector(GameObject* selected) {
	ImGui::Begin("Inspector");
	if (selected != nullptr) {
		for (auto component = selected->components.begin(); component != selected->components.end(); ++component) {
			switch ((*component)->componentType)
			{
			case ComponentType::TRANSFORM:
				showInspectorTransform(*component);
				break;
			case ComponentType::MESH:
				showInspectorMesh(*component);
				break;
			case ComponentType::TEXTURE:
				showInspectorTexture(*component);
				break;
			default:
				break;
			}
		}
	}
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showInspectorTransform(Component* component) {
	ComponentTransform* s = (ComponentTransform*)component;
	vec3f pos = { s->getPosition().x, s->getPosition().y, s->getPosition().z };
	vec3f rot = { s->getRotation().x, s->getRotation().y, s->getRotation().z };
	vec3f sca = { s->getScale().x, s->getScale().y, s->getScale().z };

	if (ImGui::TreeNode("Transform")) {
		ImGui::SeparatorText("Position");
		ImGui::DragFloat("X", &pos.x, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &pos.y, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &pos.z, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::SeparatorText("Rotate");
		ImGui::DragFloat("X", &rot.x, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &rot.y, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &rot.z, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::SeparatorText("Scale");
		ImGui::DragFloat("X", &sca.x, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Y", &sca.x, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::DragFloat("Z", &sca.x, 0.2f, 2.0f, 100.0f, "%.0f");
		ImGui::TreePop();
	}
}

void UI::showInspectorMesh(Component* component) {
	ComponentMesh* s = (ComponentMesh*)component;
	if (ImGui::TreeNode("Mesh")) {
		if (s->getMesh() != nullptr) {
			std::string path = s->getMesh()->path;
			if (auto n = path.find_last_of("\\"); n != path.npos) {
				path.erase(0, n + 1);
			}
			ImGui::Text("File:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", path.c_str());
			//if (ImGui::IsItemHovered()) {
			//	ImGui::SetTooltip("%s", (s->getMesh()->path).c_str());
			//}
			//ImGui::Text("Vertex:");
			ImGui::SameLine();
			//ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", s->getMesh()->getVertsNum());
			//ImGui::Text("Faces:", s->getMesh()->getFacesNum());
			//ImGui::SameLine();
			//ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", s->getMesh()->getFacesNum());
			if (ImGui::Checkbox("Display normals per-triangle", &triangles)) {
			// Call function in Mesh
			}
			if (ImGui::Checkbox("Display normals per-face", &faces)) {
				// Call function in Mesh
			}
		}
			//ImGui::SliderFloat("Normal's Length", &s->getMesh()->normalLineLength, 0.1f, 2.0f);
			//ImGui::SliderInt("Normal's Width", &s->getMesh()->normalLineWidth, 1, 4);
		
		else {
			ImGui::Text("Mesh not found");
		}
		ImGui::TreePop();
	}
}

void UI::showInspectorTexture(Component* component) {
	ComponentTexture* s = (ComponentTexture*)component;
	if (ImGui::TreeNode("Texture")) {
		if (s->getTexture() != nullptr) {
			string path = s->getTexture()->path;
			if (auto n = path.find_last_of("\\"); n != path.npos) {
				path.erase(0, n + 1);
			}
			ImGui::Text("File:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", path.c_str());
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("%s", s->getTexture()->path.c_str());
			}
			ImGui::Text("Size:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dpx x %dpx", s->getTexture()->width, s->getTexture()->height);
			
			if (ImGui::Checkbox("View the checkers texture", &checkerstexture)) {
				// Call the function or change the path
				//
			}
		}
		else {
			ImGui::Text("Texture not found");
		}
		ImGui::TreePop();
	}
}

void UI::showResources() {
	ImGui::Begin("Resources");
	if (ImGui::CollapsingHeader("Textures")) {

	}
	if (ImGui::CollapsingHeader("Meshes")) {

	}
	if (ImGui::CollapsingHeader("Audio")) {
		ImGui::Text("No audio files saved...");
	}
	if (ImGui::CollapsingHeader("Scenes")) {
		ImGui::Text("No scenes saved...");
	}
	if (ImGui::CollapsingHeader("Bones")) {
		ImGui::Text("No bone files saved...");
	}
	if (ImGui::CollapsingHeader("Animation")) {
		ImGui::Text("No animations saved...");
	}
	ImGui::EndMenu();
	ImGui::End();
}

void UI::showAbout(HardwareInfo hardware_info) {
	hardware_info = app->hardware->GetInfo();

	ImGui::OpenPopup("About");
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextColored(ImVec4(0.784, 0.635, 0.784, 1), "LILAC ENGINE");
		ImGui::Text("An engine in development");
		ImGui::Text("by Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
		ImGui::Text("3rd Party Libraries used:");
		// Need to change this
		ImGui::Text("- SDL 2 %s\n", hardware_info.sdl_version);
		ImGui::Text("- ImGui %s\n", IMGUI_VERSION);
		ImGui::Text("- OpenGL %\n\n", hardware_info.opengl_version);
		//ImGui::Text("- DevIL %s\n\n", (string)IMGUI_VERSION);

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
	
	static float fps[100] = {};
	static int index = 0;

	fps[index] = ImGui::GetIO().Framerate;
	index = (index + 1) % 100;

	ImGui::PlotHistogram("", fps, 100, index, "FPS", 0.0f, 100.0f, ImVec2(300, 100));
}

void UI::showHardwareInfo(HardwareInfo hardware_info) {
	// SDL Version
	ImGui::Text("SDL Version:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", hardware_info.sdl_version);

	// OpenGL Version
	ImGui::Text("OpenGL Version:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", hardware_info.opengl_version);
	ImGui::Separator();

	// CPU 
	ImGui::Text("CPU Logic Cores:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%i", hardware_info.cpu_count);

	ImGui::Text("CPU L1 Cache (Kb):");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%i", hardware_info.l1_cachekb);

	// CPU Instruction Support
	ImGui::Text("CPU Instruction Support:");
	ImGui::SameLine();

	if (hardware_info.rdtsc)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "rdtsc");
	ImGui::SameLine();
	if (hardware_info.altivec)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "altivec");
	ImGui::SameLine();
	if (hardware_info.now3d)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "now3d");
	ImGui::SameLine();
	if (hardware_info.mmx)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "mmx");
	ImGui::SameLine();
	if (hardware_info.sse)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "sse");
	ImGui::SameLine();
	if (hardware_info.sse2)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "sse2");
	ImGui::SameLine();
	if (hardware_info.sse3)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "sse3");
	ImGui::SameLine();
	if (hardware_info.sse41)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "sse41");
	ImGui::SameLine();
	if (hardware_info.sse42)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "sse42");
	ImGui::SameLine();
	if (hardware_info.avx)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "avx");
	ImGui::SameLine();
	if (hardware_info.avx2)
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", "avx2");

	// RAM 
	ImGui::Separator();
	ImGui::Text("RAM Memory (Gb)");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", hardware_info.ram_gb);

	// GPU
	ImGui::Separator();
	ImGui::Text("GPU Vendor");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", hardware_info.gpu_vendor.data());
	ImGui::Text("GPU Model");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", hardware_info.gpu_brand.data());
	ImGui::Text("GPU Driver");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%s", hardware_info.gpu_driver.data());

	// VRAM
	ImGui::Text("VRAM Budget");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", hardware_info.vram_mb_budget);
	ImGui::Text("VRAM Available");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", hardware_info.vram_mb_available);
	ImGui::Text("VRAM Usage");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", hardware_info.vram_mb_usage);
}