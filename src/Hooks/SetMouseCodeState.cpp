#include "Hooks.h"

typedef void (*SetMouseCodeState_t) (IInputInternal*, MouseCode, MouseCodeState_t);

void Hooks::SetMouseCodeState(IInputInternal* thisptr, MouseCode code, MouseCodeState_t state) {
	// Get the original function and store it statically.
	static SetMouseCodeState_t oSetMouseCodeState = inputinternal_hook->GetOriginalFunction<SetMouseCodeState_t>(84);

	// Print to console every time a mouse button is clicked, double-clicked or released.
	cvar->ConsoleColorPrintf(Color(150, 150, 255, 255), "IInputInternal::SetMouseCodeState - code: %i, state: %i\n", code, state);

	// Call original 'IInputInternal::SetMouseCodeState'.
	oSetMouseCodeState(thisptr, code, state);
}