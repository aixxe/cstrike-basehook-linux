#include "GUI.h"

bool GUI::IsVisible = false;

bool GUI::BunnyHop::Enabled = true;

bool GUI::NoSky::Enabled = true;
float GUI::NoSky::Color[3] = {0, 0, 0.275};

void GUI::Render() {
	// Draw various global components.
	GUI::DrawFramerateCounter();

	// Draw the actual configuration window.
	if (GUI::IsVisible)
		GUI::DrawConfigurationWindow();
}