#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>

namespace GUI {
	extern bool IsVisible;

	namespace BunnyHop {
		extern bool Enabled;
	}

	namespace NoSky {
		extern bool Enabled;
		extern float Color[3];
	}

	namespace ASUS {
		extern bool Enabled;
		extern float Color[4];
	}

	void DrawFramerateCounter();
	void DrawConfigurationWindow();

	void Render();
}