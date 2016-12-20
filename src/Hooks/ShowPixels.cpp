#include "Hooks.h"
#include "../GUI/GUI.h"

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

	// Enable or disable the ImGui cursor depending on the GUI visibility.
	ImGui::GetIO().MouseDrawCursor = GUI::IsVisible;
	ImGui::GetIO().WantCaptureMouse = GUI::IsVisible;
	ImGui::GetIO().WantCaptureKeyboard = GUI::IsVisible;

	// Handle incoming input while the menu is active.
	if (GUI::IsVisible) {
		SDL_Event event = {};

		while (SDL_PollEvent(&event)) {
			if (event.key.keysym.sym == SDLK_INSERT && event.type == SDL_KEYDOWN)
				GUI::IsVisible = !GUI::IsVisible;

			ImGui_ImplSdl_ProcessEvent(&event);
		}
	} 

	// Draw GUI components.
	GUI::Render();

	// Finish ImGui rendering.
	ImGui::Render();

	// Switch back to the game context.	
	launchermgr->MakeContextCurrent(original_context);

	// Call original 'ILauncherMgr::ShowPixels'.
	oShowPixels(thisptr, params);
}