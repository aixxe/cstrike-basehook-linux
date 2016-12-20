#pragma once

typedef unsigned long HFont;

enum class FontFeature: int {
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6
};

enum FontDrawType_t: int {
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2
};

enum FontFlags: int {
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = 0x1,
	FONTFLAG_UNDERLINE = 0x2,
	FONTFLAG_STRIKEOUT = 0x4,
	FONTFLAG_SYMBOL = 0x8,
	FONTFLAG_ANTIALIAS = 0x10,
	FONTFLAG_GAUSSIANBLUR = 0x20,
	FONTFLAG_ROTARY = 0x40,
	FONTFLAG_DROPSHADOW = 0x80,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800
};

class ISurface {
	public:
		void DrawSetColor(int r, int g, int b, int a) {
			GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 10)(this, r, g, b, a);
		}

		void DrawSetColor(Color color) {
			GetVirtualFunction<void(*)(ISurface*, Color)>(this, 11)(this, color);
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1) {
			GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 12)(this, x0, y0, x1, y1);
		}

		void DrawOutlinedRect(int x0, int y0, int x1, int y1) {
			GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 14)(this, x0, y0, x1, y1);
		}

		void DrawLine(int x0, int y0, int x1, int y1) {
			GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 15)(this, x0, y0, x1, y1);
		}

		void DrawSetTextFont(HFont font) {
			GetVirtualFunction<void(*)(ISurface*, HFont)>(this, 17)(this, font);
		}

		void DrawSetTextColor(int r, int g, int b, int a) {
			GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 18)(this, r, g, b, a);
		}

		void DrawSetTextColor(Color color) {
			GetVirtualFunction<void(*)(ISurface*, Color)>(this, 19)(this, color);
		}

		void DrawSetTextPos(int x, int y) {
			GetVirtualFunction<void(*)(ISurface*, int, int)>(this, 20)(this, x, y);
		}

		void DrawPrintText(const wchar_t* text, int length, FontDrawType_t type = FONT_DRAW_DEFAULT) {
			return GetVirtualFunction<void(*)(ISurface*, const wchar_t*, int, int)>(this, 22)(this, text, length, type);
		}

		HFont CreateFont() {
			return GetVirtualFunction<HFont(*)(ISurface*)>(this, 66)(this);
		}

		void SetFontGlyphSet(HFont& font, const char* name, int tall, int weight, int blur, int scanlines, FontFlags flags = FONTFLAG_NONE) {
			GetVirtualFunction<void(*)(ISurface*, HFont, const char*, int, int, int, int, FontFlags, int, int)>(this, 67)(this, font, name, tall, weight, blur, scanlines, flags, 0, 0);
		}

		void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall) {
			GetVirtualFunction<void(*)(ISurface*, HFont, const wchar_t*, int&, int&)>(this, 75)(this, font, text, wide, tall);
		}
		
		void GetCursorPos(int& x, int& y) {
			return GetVirtualFunction<void(*)(ISurface*, int&, int&)>(this, 96)(this, x, y);
		}

		void DrawOutlinedCircle(int x, int y, int radius, int segments) {
			return GetVirtualFunction<void(*)(ISurface*, int, int, int, int)>(this, 99)(this, x, y, radius, segments);
		}
};

extern ISurface* matsurface;