#include "Hooks.h"

typedef void (*SetKeyCodeState_t) (IInputInternal*, KeyCode, bool);

void Hooks::SetKeyCodeState(IInputInternal* thisptr, KeyCode code, bool pressed) {
	// Get the original function and store it statically.
	static SetKeyCodeState_t oSetKeyCodeState = inputinternal_hook->GetOriginalFunction<SetKeyCodeState_t>(83);

	// Print to console every time a key is pressed or released.
	cvar->ConsoleColorPrintf(Color(150, 150, 255, 255), "IInputInternal::SetKeyCodeState - code: %i, pressed: %i\n", code, pressed);

	// Call original 'IInputInternal::SetKeyCodeState'.
	oSetKeyCodeState(thisptr, code, pressed);
}