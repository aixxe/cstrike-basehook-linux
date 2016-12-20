#pragma once

class ICvar {
	public:
		template <typename... Values> void ConsoleColorPrintf(const Color& MsgColor, const char* Format, Values... Parameters) {
			return GetVirtualFunction<void(*)(ICvar*, const Color&, const char*, ...)>(this, 23)(this, MsgColor, Format, Parameters...);
		}

		template <typename... Values> void ConsoleDPrintf(const char* Format, Values... Parameters) {
			return GetVirtualFunction<void(*)(ICvar*, const char*, ...)>(this, 24)(this, Format, Parameters...);
		}
};

extern ICvar* cvar;