#pragma once

#include "../Basehook.h"
#include "../GUI/GUI.h"

namespace Hooks {
	// IBaseClientDLL
	void CreateMove(IBaseClientDLL*, int, float, bool); 
	void FrameStageNotify(IBaseClientDLL*, ClientFrameStage_t);

	// IPanel
	void PaintTraverse(IPanel*, VPANEL, bool, bool);

	// IVModelRender
	void DrawModelExecute(IVModelRender*, DrawModelState_t const&, ModelRenderInfo_t const&, matrix3x4_t*);
	
	// ILauncherMgr
	void PumpWindowsMessageLoop(ILauncherMgr*);
	void ShowPixels(ILauncherMgr*, CShowPixelsParams*);

	// IInputInternal
	void SetKeyCodeState(IInputInternal*, KeyCode, bool);
	void SetMouseCodeState(IInputInternal*, MouseCode, MouseCodeState_t);
}

extern std::unique_ptr<VMTHook> sdl_hook;
extern std::unique_ptr<VMTHook> panel_hook;
extern std::unique_ptr<VMTHook> clientdll_hook;
extern std::unique_ptr<VMTHook> modelrender_hook;
extern std::unique_ptr<VMTHook> inputinternal_hook;