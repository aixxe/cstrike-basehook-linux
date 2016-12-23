#include "Hooks.h"

extern StartDrawing_t StartDrawing;
extern FinishDrawing_t FinishDrawing;

typedef void (*Paint_t) (IEngineVGui*, PaintMode_t);

void Hooks::Paint(IEngineVGui* thisptr, PaintMode_t mode) {
	// Get the original function and store it statically.
	static Paint_t oPaint = enginevgui_hook->GetOriginalFunction<Paint_t>(14);

	// Call original 'IEngineVGui::Paint'.
	oPaint(thisptr, mode);

	if (mode & PaintMode_t::PAINT_UIPANELS) {
		StartDrawing(matsurface);

		// Set watermark text.
		const wchar_t* watermark = L"cstrike-basehook-linux";

		// Set position of watermark text. (bottom-right)
		int width = 0, height = 0, wide = 0, tall = 0;
		engine->GetScreenSize(width, height);
		matsurface->GetTextSize(37, watermark, wide, tall);

		// Do stuff here then call FinishDrawing.
		matsurface->DrawSetTextColor(Color(150, 150, 255));
		matsurface->DrawSetTextPos((width - wide) - 15, (height - tall) - 15);
		matsurface->DrawSetTextFont(37);
		matsurface->DrawPrintText(L"cstrike-basehook-linux", 23);

		FinishDrawing(matsurface);
	}
}