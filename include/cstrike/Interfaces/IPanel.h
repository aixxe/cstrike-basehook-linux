#pragma once

typedef unsigned long VPANEL;

class IPanel {
	public:
		const char* GetName(VPANEL vpanel) {
			return GetVirtualFunction<const char*(*)(IPanel*, VPANEL)>(this, 37)(this, vpanel);
		}

		void PaintTraverse(VPANEL vpanel, bool force_repaint, bool allow_force) {
			GetVirtualFunction<void(*)(IPanel*, VPANEL, bool, bool)>(this, 42)(this, vpanel, force_repaint, allow_force);
		}
};

extern IPanel* panel;