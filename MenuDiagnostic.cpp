#include "MenuDiagnostic.h"
#include "Imgui/imgui.h"

#define FPS_SIZE 50

// ------------------------------------------------------------
MenuDiagnostic::MenuDiagnostic() : Menu(Menu_Diagnostic), fps(FPS_SIZE)
{
	pos_x = 2;
	pos_y = 499;
	width = 275;
	height = 475;
}

// ------------------------------------------------------------
MenuDiagnostic::~MenuDiagnostic()
{}

// ------------------------------------------------------------
void MenuDiagnostic::Render()
{
	
	ImGui::Begin("Diagnostic tool", &active,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_HorizontalScrollbar);

	if (ImGui::Button("Set Default"))
	{ 
		printf("Clicked\n"); 
		// Reset all changes
	}

	// CalculateFPS();
	
	if (ImGui::CollapsingHeader("Graphs"))
	{
		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", fps[fps.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 100.0f, ImVec2(250, 100));
	}	
	
	ImGui::End();
}

void MenuDiagnostic::CalculateFPS(float current_fps)
{
	if (bar_num == FPS_SIZE)
	{
		for (uint i = 0; i < FPS_SIZE - 1; ++i)
		{
			fps[i] = fps[i + 1];
		}
	}
	else
		++bar_num;

	fps[bar_num - 1] = current_fps;
}
