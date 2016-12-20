#include "Hooks.h"

typedef void (*PaintTraverse_t) (IPanel*, VPANEL, bool, bool);

void Hooks::PaintTraverse(IPanel* thisptr, VPANEL vpanel, bool force_repaint, bool allow_force) {
	// Get the original function and store it statically.
	static PaintTraverse_t oPaintTraverse = panel_hook->GetOriginalFunction<PaintTraverse_t>(42);

	// Call original 'IPanel::PaintTraverse'.
	oPaintTraverse(thisptr, vpanel, force_repaint, allow_force);
}