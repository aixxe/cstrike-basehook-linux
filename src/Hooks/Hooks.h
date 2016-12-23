#pragma once

#include "../Basehook.h"
#include "../GUI/GUI.h"

// Extra functions neccessary for proper engine drawing.
typedef void (*StartDrawing_t) (ISurface*);
typedef void (*FinishDrawing_t) (ISurface*);

namespace Hooks {
	// ILauncherMgr
	void PumpWindowsMessageLoop(ILauncherMgr*);
	void ShowPixels(ILauncherMgr*, CShowPixelsParams*);

	// IBaseClientDLL
	void CreateMove(IBaseClientDLL*, int, float, bool); 
	void FrameStageNotify(IBaseClientDLL*, ClientFrameStage_t);

	// IEngineVGui
	void Paint(IEngineVGui*, PaintMode_t);

	// IVModelRender
	void DrawModelExecute(IVModelRender*, DrawModelState_t const&, ModelRenderInfo_t const&, matrix3x4_t*);

	// IInputInternal
	void SetKeyCodeState(IInputInternal*, KeyCode, bool);
	void SetMouseCodeState(IInputInternal*, MouseCode, MouseCodeState_t);
}

extern std::unique_ptr<VMTHook> sdl_hook;
extern std::unique_ptr<VMTHook> clientdll_hook;
extern std::unique_ptr<VMTHook> enginevgui_hook;
extern std::unique_ptr<VMTHook> modelrender_hook;
extern std::unique_ptr<VMTHook> inputinternal_hook;