#pragma once

enum ButtonCode_t;

class IInputSystem {
	public:
		bool IsButtonDown(ButtonCode_t button) {
			return GetVirtualFunction<bool(*)(void*, ButtonCode_t)>(this, 11)(this, button);
		}
};