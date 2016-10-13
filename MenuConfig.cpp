#include "MenuConfig.h"
#include "Application.h"
#include "Imgui/imgui.h"

#define GRAPH_SIZE 75

// ------------------------------------------------------------
MenuConfig::MenuConfig() : Menu(Menu_Config), fps(GRAPH_SIZE), ms(GRAPH_SIZE), new_width(App->window->GetWidth()), new_height(App->window->GetHeight())
{
	pos_x = 2;
	pos_y = (App->window->GetHeight()) - (((App->window->GetHeight()) - 19 - 6) / 2) - 2;	// Provisional :(
	width = 250;
	height = (((App->window->GetHeight()) - 19 - 6) / 2);
	
	// Hardware window ----------------------------
	SDL_version sdl_compiled;
	SDL_VERSION(&sdl_compiled);
	sprintf_s(sdl_compiled_info, 20, "%i.%i.%i", sdl_compiled.major, sdl_compiled.minor, sdl_compiled.patch);
	
	cpu_number = SDL_GetCPUCount();
	cpu_cache = SDL_GetCPUCacheLineSize();
	system_ram = SDL_GetSystemRAM();	// MB
	caps_rdtsc = SDL_HasRDTSC();
	caps_mmx = SDL_HasMMX();
	caps_sse = SDL_HasSSE();
	caps_sse2 = SDL_HasSSE2();
	caps_sse3 = SDL_HasSSE3();
	caps_sse41 = SDL_HasSSE41();
	caps_sse42 = SDL_HasSSE42();
	caps_avx = SDL_HasAVX();
	caps_avx2 = SDL_HasAVX2();
	caps_altivec = SDL_HasAltiVec();
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
		char title[20];
		sprintf_s(title, 20, "Framerate %.1f", fps[fps.size() - 1]);
		ImGui::PlotHistogram("##frame", &fps[0], fps.size(), 0, title, 0.0f, 100.0f, ImVec2(215, 70));
		sprintf_s(title, 20, "Milliseconds %.1f", ms[ms.size() - 1]);
		ImGui::PlotHistogram("##milli", &ms[0], ms.size(), 0, title, 0.0f, 30.0f, ImVec2(215, 70));
	}

	// Window window ----------------------------
	fullscreen = App->window->GetFullscreen();
	resizable = App->window->GetResizable();
	borderless = App->window->GetBorderlees();

	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::Button("Default"))
		{
			App->window->SetDefaultSize();
			new_width = App->window->GetWidth();
			new_height = App->window->GetHeight();
		}

		ImGui::Separator();	// ------

		if (ImGui::DragInt("Width", &new_width, 1, 800, 1680))
		{
			ImGui::SameLine();
			ShowHelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");
			App->window->SetWidth(new_width);
			// SetMenuPos();
		}

		if (ImGui::DragInt("Height", &new_height, 1, 600, 1050))
		{
			ImGui::SameLine();
			ShowHelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");
			App->window->SetHeight(new_height);
			// SetMenuPos(); & SetMenuSize();
		}

		ImGui::Separator();	// ------

		if (ImGui::Checkbox("Fullscreen", &fullscreen))
			App->window->SetFullscreen(fullscreen);

		if (ImGui::Checkbox("Borderless", &borderless))
			App->window->SetBorderless(borderless);

		ImGui::SameLine();

		if (ImGui::Checkbox("Resizable", &resizable))
			App->window->SetResizable(resizable);
	}

	// Hardware window ----------------------------
	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("SDL Version:"); ImGui::SameLine();	// Adjust spacing
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), sdl_compiled_info);

		ImGui::Separator();	// ------

		ImGui::Text("CPUs:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%u  (Cache: %u KB)", cpu_number, cpu_cache);

		ImGui::Text("System RAM:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%u MB", system_ram);

		ImGui::Text("Caps:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%s%s%s%s", caps_rdtsc ? "RDTSC," : "",
			caps_mmx ? "MMX," : "",
			caps_sse ? "SSE," : "",
			caps_sse2 ? "SSE2," : "");
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%s%s%s%s", caps_sse3 ? "SEE3," : "",
			caps_sse41 ? "SEE41," : "",
			caps_sse42 ? "SEE42," : "",
			caps_avx ? "AVX," : "");
		ImGui::TextColored(ImVec4(0.25f, 0.88f, 0.81f, 0.70f), "%s%s", caps_avx2 ? "AVX2," : "",
			caps_altivec ? "ALTIVEC" : "");
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