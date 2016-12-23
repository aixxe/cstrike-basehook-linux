#include "GUI.h"

bool GUI::IsVisible = false;

void GUI::Render() {
	// Draw various global components.
	GUI::DrawFramerateCounter();

	// Draw the actual configuration window.
	if (GUI::IsVisible)
		GUI::DrawConfigurationWindow();
}