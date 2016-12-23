/*

	cstrike-basehook-linux -- Internal base for Counter-Strike: Source.
	Copyright (C) 2016, aixxe. (www.aixxe.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cstrike-basehook-linux. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Basehook.h"
#include "Hooks/Hooks.h"

ICvar* cvar = nullptr;
IPanel* panel = nullptr;
ISurface* matsurface = nullptr;
IEngineVGui* enginevgui = nullptr;
IVModelInfoClient* modelinfo = nullptr;
ILauncherMgr* launchermgr = nullptr;
IInputSystem* inputsystem = nullptr;
IInputInternal* inputinternal = nullptr;
IVEngineClient* engine = nullptr;
IVModelRender* modelrender = nullptr;
IVDebugOverlay* debugoverlay = nullptr;
IBaseClientDLL* clientdll = nullptr;
IMaterialSystem* matsystem = nullptr;
IClientEntityList* entitylist = nullptr;
IGameEventManager2* gameevents = nullptr;

CInput* input = nullptr;
CGlobalVarsBase* globalvars = nullptr;

CRC32_ProcessBufferFn CRC32_ProcessBuffer = NULL;

StartDrawing_t StartDrawing = NULL;
FinishDrawing_t FinishDrawing = NULL;

std::unique_ptr<VMTHook> sdl_hook;
std::unique_ptr<VMTHook> clientdll_hook;
std::unique_ptr<VMTHook> enginevgui_hook;
std::unique_ptr<VMTHook> modelrender_hook;
std::unique_ptr<VMTHook> inputinternal_hook;

extern "C" void __attribute__((constructor)) css_basehook_open() {
	// Get class pointers from game libraries using partial interface versions.
	cvar = GetInterface<ICvar>("bin/libvstdlib.so", "VEngineCvar0");
	panel = GetInterface<IPanel>("bin/vgui2.so", "VGUI_Panel0");
	matsurface = GetInterface<ISurface>("bin/vguimatsurface.so", "VGUI_Surface0");
	enginevgui = GetInterface<IEngineVGui>("bin/engine.so", "VEngineVGui0");
	modelinfo = GetInterface<IVModelInfoClient>("bin/engine.so", "VModelInfoClient0"); 
	inputsystem = GetInterface<IInputSystem>("bin/inputsystem.so", "InputSystemVersion0");
	inputinternal = GetInterface<IInputInternal>("bin/vgui2.so", "VGUI_InputInternal0");
	engine = GetInterface<IVEngineClient>("bin/engine.so", "VEngineClient0");
	modelrender = GetInterface<IVModelRender>("bin/engine.so", "VEngineModel0");
	debugoverlay = GetInterface<IVDebugOverlay>("bin/engine.so", "VDebugOverlay0");
	clientdll = GetInterface<IBaseClientDLL>("bin/client.so", "VClient0");
	matsystem = GetInterface<IMaterialSystem>("bin/materialsystem.so", "VMaterialSystem0");
	entitylist = GetInterface<IClientEntityList>("bin/client.so", "VClientEntityList0");
	gameevents = GetInterface<IGameEventManager2>("bin/engine.so", "GAMEEVENTSMANAGER002");

	// Scan for the 'CRC32_ProcessBuffer' function. 
	CRC32_ProcessBuffer = reinterpret_cast<CRC32_ProcessBufferFn>(
		FindPattern("bin/client.so", "\x55\x89\xE5\x57\x56\x53\x83\xEC\x08\x8B\x4D\x10", "xxxxxxxxxxxx")
	);

	// Hook 'FrameStageNotify' and 'CreateMove' from IBaseClientDLL.
	clientdll_hook = std::make_unique<VMTHook>(clientdll);
	clientdll_hook->HookFunction(reinterpret_cast<void*>(Hooks::CreateMove), 21);
	clientdll_hook->HookFunction(reinterpret_cast<void*>(Hooks::FrameStageNotify), 35);

	// Scan for 'StartDrawing' and 'FinishDrawing' from CMatSystemSurface.
	StartDrawing = reinterpret_cast<StartDrawing_t>(
		FindPattern("bin/vguimatsurface.so", "\x55\x89\xE5\x53\x83\xEC\x74\x80\x3D\x00\x00\x00\x00\x00", "xxxxxxxxx????x")
	);

	FinishDrawing = reinterpret_cast<FinishDrawing_t>(
		FindPattern("bin/vguimatsurface.so", "\x55\x89\xE5\x53\x83\xEC\x24\xC7\x04\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xA1", "xxxxxxxxx????xx????x")
	);

	// Hook 'Paint' from IEngineVGui.
	enginevgui_hook = std::make_unique<VMTHook>(enginevgui);
	enginevgui_hook->HookFunction(reinterpret_cast<void*>(Hooks::Paint), 14);

	// Hook 'DrawModelExecute' from IVModelRender.
	modelrender_hook = std::make_unique<VMTHook>(modelrender);
	modelrender_hook->HookFunction(reinterpret_cast<void*>(Hooks::DrawModelExecute), 19);

	// Hook 'PumpWindowsMessageLoop' and 'ShowPixels' from ILauncherMgr.
	launchermgr = **reinterpret_cast<ILauncherMgr***>(
		FindPattern("bin/launcher.so", "\x24\x8B\x1D\x00\x00\x00\x00", "xxx????") + 3
	);

	sdl_hook = std::make_unique<VMTHook>(launchermgr);
	sdl_hook->HookFunction(reinterpret_cast<void*>(Hooks::PumpWindowsMessageLoop), 15);
	sdl_hook->HookFunction(reinterpret_cast<void*>(Hooks::ShowPixels), 29);

	// Hook 'SetKeyCodeState' and 'SetMouseCodeState' from IInputInternal.
	inputinternal_hook = std::make_unique<VMTHook>(inputinternal);
	inputinternal_hook->HookFunction(reinterpret_cast<void*>(Hooks::SetKeyCodeState), 83);
	inputinternal_hook->HookFunction(reinterpret_cast<void*>(Hooks::SetMouseCodeState), 84);

	// Get a pointer to CInput from 'IN_ActivateMouse' in IBaseClientDLL.
	input = **reinterpret_cast<CInput***>(
		clientdll_hook->GetOriginalFunction<uintptr_t>(14) + 1
	);
	
	// Get a pointer to CGlobalVarsBase from 'HUDUpdate' in IBaseClientDLL.
	globalvars = **reinterpret_cast<CGlobalVarsBase***>(
		clientdll_hook->GetOriginalFunction<uintptr_t>(11) + 8
	);
}

extern "C" void __attribute__((destructor)) css_basehook_close() {
	cvar->ConsoleColorPrintf(Color(255, 150, 150), "Unloaded from game successfully.\n");
}