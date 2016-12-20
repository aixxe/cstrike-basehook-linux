#include "Hooks.h"

typedef void (*SetKeyCodeState_t) (IInputInternal*, KeyCode, bool);

void Hooks::SetKeyCodeState(IInputInternal* thisptr, KeyCode code, bool down) {
	// Get the original function and store it statically.
	static SetKeyCodeState_t oSetKeyCodeState = inputinternal_hook->GetOriginalFunction<SetKeyCodeState_t>(83);

	// Print to console every time a key is pressed or released.
	cvar->ConsoleColorPrintf(Color(150, 150, 255, 255), "IInputInternal::SetKeyCodeState - code: %i, down: %i\n", code, down);

	// Check if we should open the menu.
	if (code == KeyCode::KEY_INSERT && down == false)
		GUI::IsVisible = true;

	// Call original 'IInputInternal::SetKeyCodeState'.
	oSetKeyCodeState(thisptr, code, down);
}