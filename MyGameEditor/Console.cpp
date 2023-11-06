#include "Console.h"
#include "Application.h"
#include "UI.h"
#include "imgui.h"

#include "log.h"

Console::Console(){}

Console::~Console() {}

bool Console::Draw()
{
	ImGuiWindowFlags consoleFlags = 0;
	consoleFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

	if (ImGui::Begin("Console"))
	{
		if (ImGui::SmallButton("Clear"))
			App->ClearLogs();

		ImGui::Separator();

		ImGuiWindowFlags scrollFlags = 0;
		scrollFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		scrollFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

		if (ImGui::BeginChild("Scrollbar", ImVec2(0, 0), false, scrollFlags))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 1));



			for (const auto& log : App->GetLogs())
			{
				
				
				ImGui::TextUnformatted(log.data());
				ImGui::PopStyleColor();
			}

			ImGui::PopStyleVar();

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

			ImGui::EndChild();
		}

		ImGui::End();
	}

	return true;
}