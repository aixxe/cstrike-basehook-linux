#include "Hooks.h"

typedef void (*FrameStageNotify_t) (IBaseClientDLL*, ClientFrameStage_t);

void Hooks::FrameStageNotify(IBaseClientDLL* thisptr, ClientFrameStage_t stage) {
	// Get the original function and store it statically.
	static FrameStageNotify_t oFrameStageNotify = clientdll_hook->GetOriginalFunction<FrameStageNotify_t>(35);

	// Call original 'IBaseClientDLL::FrameStageNotify'.
	oFrameStageNotify(thisptr, stage);
}