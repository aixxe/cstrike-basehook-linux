#include "GUI.h"

void GUI::DrawFramerateCounter() {
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("FPS", nullptr, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void GUI::DrawConfigurationWindow() {
	ImGui::Begin("Settings", nullptr);
	ImGui::PushItemWidth(-1);

	ImGui::Checkbox("Auto-bunnyhop", &GUI::BunnyHop::Enabled);
	ImGui::Spacing();

	ImGui::Checkbox("No sky", &GUI::NoSky::Enabled);
	ImGui::ColorEdit3("##No sky color", GUI::NoSky::Color);
	ImGui::Spacing();

	ImGui::Checkbox("ASUS walls", &GUI::ASUS::Enabled);
	ImGui::ColorEdit4("##ASUS walls color", GUI::ASUS::Color, true);
	ImGui::Spacing();
	
	ImGui::PopItemWidth();
	ImGui::End();
}
