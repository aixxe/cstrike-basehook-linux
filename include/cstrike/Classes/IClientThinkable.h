#pragma once

class IClientThinkable {
	public:
		virtual IClientUnknown* GetIClientUnknown() = 0;
};