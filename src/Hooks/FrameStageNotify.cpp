#include <unordered_map>

#include "Hooks.h"

typedef void (*FrameStageNotify_t) (IBaseClientDLL*, ClientFrameStage_t);

bool GUI::NoSky::Enabled = true;
float GUI::NoSky::Color[3] = {0, 0, 0.275};

bool GUI::ASUS::Enabled = true;
float GUI::ASUS::Color[4] = {1, 1, 1, 0.75};

std::unordered_map<MaterialHandle_t, ImColor> material_colors;

void Hooks::FrameStageNotify(IBaseClientDLL* thisptr, ClientFrameStage_t stage) {
	// Get the original function and store it statically.
	static FrameStageNotify_t oFrameStageNotify = clientdll_hook->GetOriginalFunction<FrameStageNotify_t>(35);

	// Restore skybox & world materials to original state when disconnected.
	if (!engine->IsConnected() && material_colors.size() > 0) {
		for (const auto& it: material_colors) {
			IMaterial* material = matsystem->GetMaterial(it.first);

			material->ColorModulate(1, 1, 1);
			material->AlphaModulate(1);
		}

		material_colors.clear();
	}

	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
		for (MaterialHandle_t i = matsystem->FirstMaterial(); i != matsystem->InvalidMaterial(); i = matsystem->NextMaterial(i)) {
			// Get the material from the current handle.
			IMaterial* material = matsystem->GetMaterial(i);

			// Check for 'SkyBox textures' group.
			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX)) {
				if (material_colors.find(i) == material_colors.end())
					material_colors.emplace(i, ImColor());

				ImColor color = ImColor(1.0f, 1.0f, 1.0f);

				if (GUI::NoSky::Enabled)
					color = ImColor(GUI::NoSky::Color[0], GUI::NoSky::Color[1], GUI::NoSky::Color[2]);

				if (material_colors.at(i) != color) {
					material->ColorModulate(color.Value.x, color.Value.y, color.Value.z);

					material_colors.at(i) = color;
				}

				continue;
			}

			// Check for 'World textures' group.
			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_WORLD)) {
				if (material_colors.find(i) == material_colors.end())
					material_colors.emplace(i, ImColor());

				ImColor color = ImColor(1.0f, 1.0f, 1.0f);

				if (GUI::ASUS::Enabled)
					color = ImColor(GUI::ASUS::Color[0], GUI::ASUS::Color[1], GUI::ASUS::Color[2], GUI::ASUS::Color[3]);

				if (material_colors.at(i) != color) {
					material->ColorModulate(color.Value.x, color.Value.y, color.Value.z);
					material->AlphaModulate(color.Value.w);

					material_colors.at(i) = color;
				}
			}
		}
	}

	// Call original 'IBaseClientDLL::FrameStageNotify'.
	oFrameStageNotify(thisptr, stage);
}