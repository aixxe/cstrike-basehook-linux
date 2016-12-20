#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>

namespace GUI {
	extern bool IsVisible;

	void DrawFramerateCounter();
	void DrawConfigurationWindow();

	void Render();
}