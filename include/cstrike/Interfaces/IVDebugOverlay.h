#pragma once

class IVDebugOverlay {
	public:
		bool ScreenPosition(const Vector& world, Vector& screen) {
			return GetVirtualFunction<int(*)(IVDebugOverlay*, const Vector&, Vector&)>(this, 9)(this, world, screen) == 0;
		}
};