#pragma once

typedef ButtonCode_t KeyCode;
typedef ButtonCode_t MouseCode;

enum MouseCodeState_t {
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED,
	BUTTON_DOUBLECLICKED
};

class IInputInternal {
	public:
		void SetKeyCodeState(KeyCode code, bool pressed) {
			GetVirtualFunction<void(*)(IInputInternal*, KeyCode, bool)>(this, 83)(this, code, pressed);
		}

		void SetMouseCodeState(MouseCode code, MouseCodeState_t state) {
			GetVirtualFunction<void(*)(IInputInternal*, MouseCode, MouseCodeState_t)>(this, 84)(this, code, state);
		}
};

extern IInputInternal* inputinternal;