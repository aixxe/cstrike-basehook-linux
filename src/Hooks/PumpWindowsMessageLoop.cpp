#include "Hooks.h"

typedef void (*PumpWindowsMessageLoop_t) (ILauncherMgr*);

void Hooks::PumpWindowsMessageLoop(ILauncherMgr* thisptr) {
	// Get the original function and store it statically.
	static PumpWindowsMessageLoop_t oPumpWindowsMessageLoop = sdl_hook->GetOriginalFunction<PumpWindowsMessageLoop_t>(15);

	// Block game input while the GUI is visible.
	if (GUI::IsVisible)
		return;

	// Call original 'ILauncherMgr::PumpWindowsMessageLoop'.
	oPumpWindowsMessageLoop(thisptr);
}