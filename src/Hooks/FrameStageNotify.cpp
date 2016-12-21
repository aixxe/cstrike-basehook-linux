#include "Hooks.h"

typedef void (*FrameStageNotify_t) (IBaseClientDLL*, ClientFrameStage_t);

void Hooks::FrameStageNotify(IBaseClientDLL* thisptr, ClientFrameStage_t stage) {
	// Get the original function and store it statically.
	static FrameStageNotify_t oFrameStageNotify = clientdll_hook->GetOriginalFunction<FrameStageNotify_t>(35);

	// Really should move this somewhere else. Doesn't need to be called this often.
	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END) {
		for (MaterialHandle_t i = matsystem->FirstMaterial(); i != matsystem->InvalidMaterial(); i = matsystem->NextMaterial(i)) {
			IMaterial* material = matsystem->GetMaterial(i);

			// No Sky
			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX)) {
				if (GUI::NoSky::Enabled) {
					material->ColorModulate(GUI::NoSky::Color[0], GUI::NoSky::Color[1], GUI::NoSky::Color[2]);
				} else {
					material->ColorModulate(1, 1, 1);
				}

				continue;
			}

			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_WORLD)) {
				// ASUS walls.
				if (GUI::ASUS::Enabled) {
					material->ColorModulate(GUI::ASUS::Color[0], GUI::ASUS::Color[1], GUI::ASUS::Color[2]);
					material->AlphaModulate(GUI::ASUS::Color[3]);
				} else {
					material->ColorModulate(1, 1, 1);
					material->AlphaModulate(1);
				}
			}
		}
	}

	// Call original 'IBaseClientDLL::FrameStageNotify'.
	oFrameStageNotify(thisptr, stage);
}