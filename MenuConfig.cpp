#include "MenuConfig.h"
#include "Application.h"
#include "Imgui/imgui.h"

#define GRAPH_SIZE 50

// ------------------------------------------------------------
MenuConfig::MenuConfig() : Menu(Menu_Config), fps(GRAPH_SIZE), ms(GRAPH_SIZE), new_width(App->window->GetWidth())
{
	pos_x = 2;
	pos_y = 499;
	width = 275;
	height = 475;
}

// ------------------------------------------------------------
MenuConfig::~MenuConfig()
{}

// ------------------------------------------------------------
void MenuConfig::Render()
{
	
	ImGui::Begin("Configuration", &active,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_HorizontalScrollbar);

	// CalculateParameters();
	
	// Graph window ----------------------------
	if (ImGui::CollapsingHeader("Graphs"))
	{
		ColorButton(4);

		if (ImGui::Button("Default"))
		{
			// Reset all changes
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator(); // ------

		char title[20];
		sprintf_s(title, 20, "Framerate %.1f", fps[fps.size() - 1]);
		ImGui::PlotHistogram("##frame", &fps[0], fps.size(), 0, title, 0.0f, 100.0f, ImVec2(250, 70));
		sprintf_s(title, 20, "Milliseconds %.1f", ms[ms.size() - 1]);
		ImGui::PlotHistogram("##milli", &ms[0], ms.size(), 0, title, 0.0f, 30.0f, ImVec2(250, 70));
	}

	fullscreen = App->window->GetFullscreen();
	resizable = App->window->GetResizable();
	borderless = App->window->GetBorderlees();

	// Window window ----------------------------
	if (ImGui::CollapsingHeader("Window"))
	{
		ColorButton(4);

		if (ImGui::Button("Default"))
		{
			// Reset all changes
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator();	// ------

		ImGui::DragInt("Width", &new_width, 1, 500, 1750);
		ImGui::SameLine(); 
		ShowHelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");
		App->window->SetWidth(new_width);

		ImGui::Separator();	// ------

		if (ImGui::Checkbox("Fullscreen", &fullscreen))
			App->window->SetFullscreen(fullscreen);

		if (ImGui::Checkbox("Borderless", &borderless))
			App->window->SetBorderless(borderless);

		ImGui::SameLine();

		if (ImGui::Checkbox("Resizable", &resizable))
			App->window->SetResizable(resizable);
	}
	
	ImGui::End();
}

// ------------------------------------------------------------
void MenuConfig::CalculateParameters(float current_fps, float current_ms)
{
	if (bar_num == GRAPH_SIZE)
	{
		for (uint i = 0; i < GRAPH_SIZE - 1; i++)
		{
			fps[i] = fps[i + 1];
			ms[i] = ms[i + 1];
		}
	}
	else
		bar_num++;

	fps[bar_num - 1] = current_fps;
	ms[bar_num - 1] = current_ms;
}