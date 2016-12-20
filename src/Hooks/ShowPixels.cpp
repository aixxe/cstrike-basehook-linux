#include "Hooks.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>

typedef void (*ShowPixels_t) (ILauncherMgr*, CShowPixelsParams*);

void Hooks::ShowPixels(ILauncherMgr* thisptr, CShowPixelsParams* params) {
	// Get the original function and store it statically.
	static ShowPixels_t oShowPixels = sdl_hook->GetOriginalFunction<ShowPixels_t>(29);

	if (!params->m_noBlit)
		return oShowPixels(thisptr, params);

	// Also store the game window, original and user contexts statically.
	static SDL_Window* window = reinterpret_cast<SDL_Window*>(launchermgr->GetWindowRef());
	
	static PseudoGLContextPtr original_context = launchermgr->GetMainContext();
	static PseudoGLContextPtr user_context = nullptr;

	// Set up our context on first execution.
	if (!user_context) {
		user_context = launchermgr->CreateExtraContext();
		ImGui_ImplSdl_Init(window);
	}
	
	// Switch to our context.
	launchermgr->MakeContextCurrent(user_context);

	// Start ImGui rendering.
	ImGui_ImplSdl_NewFrame(window);

	// Draw some test stuff.
	ImGui::Text("Hello, world!");

	// Finish ImGui rendering.
	ImGui::Render();

	// Switch back to the game context.	
	launchermgr->MakeContextCurrent(original_context);

	// Call original 'ILauncherMgr::ShowPixels'.
	oShowPixels(thisptr, params);
}