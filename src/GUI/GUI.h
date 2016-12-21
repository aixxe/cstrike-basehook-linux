#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>

namespace GUI {
	extern bool IsVisible;

	namespace BunnyHop {
		extern bool Enabled;
	}

	void DrawFramerateCounter();
	void DrawConfigurationWindow();

	void Render();
}