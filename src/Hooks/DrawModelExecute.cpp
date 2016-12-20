#include "Hooks.h"

typedef void (*DrawModelExecute_t) (IVModelRender*, DrawModelState_t const&, ModelRenderInfo_t const&, matrix3x4_t*);

void Hooks::DrawModelExecute(IVModelRender* thisptr, DrawModelState_t const& drawmodelstate, ModelRenderInfo_t const& modelrenderinfo, matrix3x4_t* bonetoworld) {
	// Get the original function and store it statically.
	static DrawModelExecute_t oDrawModelExecute = modelrender_hook->GetOriginalFunction<DrawModelExecute_t>(19);
	
	// Call original 'IVModelRender::DrawModelExecute'.
	oDrawModelExecute(thisptr, drawmodelstate, modelrenderinfo, bonetoworld);
}