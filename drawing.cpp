#include "hooks.h"

HFont Fonts::m_MenuFont;
HFont Fonts::m_ListItemFont;
HFont Fonts::m_WatermarkFont;
HFont Fonts::m_VelocityFont;

VOID Draw::InitFonts()
{
	if (pSurface == NULL)
		return;

	pSurface->SetFontGlyphSet(Fonts::m_MenuFont = pSurface->Create_Font(), "Visitor TT2 BRK", 15, 500, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_ListItemFont = pSurface->Create_Font(), "Visitor TT2 BRK", 13, 500, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_WatermarkFont = pSurface->Create_Font(), "Tahoma", 13, 700, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_VelocityFont = pSurface->Create_Font(), "Tahoma", 24, 700, 0, 0, 0x200);
}

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))
void Draw::DrawMonitorBar(int x, int y, int cur, const char* title)
{
	cur = clamp(cur, 0, 100);

	Draw::FillRGBA(x, y, 30, 160, (int)(cur*2.55), (255 - (int)(cur*2.55)), 0, 255);
	Draw::FillRGBA(x, y, 30, 160 - (cur * 1.6), 0, 0, 0, 255);
	Draw::DrawStringA(Fonts::m_ListItemFont, false, x, y + 169, 255, 255, 255, 255, title);
}

void Draw::OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Draw::FillRGBA(x, y, w, 1, r, g, b, a);
	Draw::FillRGBA(x, y, 1, h, r, g, b, a);
	Draw::FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
	Draw::FillRGBA(x, y + h, w, 1, r, g, b, a);
}

void Draw::DrawTexts(unsigned long font, int x, int y, int r, int g, int b, int a, const wchar_t * text)
{
	pSurface->DrawSetTextPos(x, y);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextColor(r, g, b, a);
	pSurface->DrawPrintText(text, wcslen(text));
}

void Draw::SoftOutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Draw::FillRGBA(x + 2, y, w - 3, 1, r, g, b, a);
	Draw::FillRGBA(x + 1, y + 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x, y + 2, 1, h - 3, r, g, b, a);
	Draw::FillRGBA(x + 1, y + h - 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x + w, y + 2, 1, h - 3, r, g, b, a);
	Draw::FillRGBA(x + w - 1, y + 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x + 2, y + h, w - 3, 1, r, g, b, a);
	Draw::FillRGBA(x + w - 1, y + h - 1, 1, 1, r, g, b, a);
}

void Draw::FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	pSurface->DrawSetColor(r, g, b, a);
	pSurface->DrawFilledRect(x, y, x + w, y + h);
}

std::wstring Draw::stringToWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

int Draw::getWidht(unsigned long font, const char* input)
{
	INT iWide = 0;
	INT iTall = 0;
	INT iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

	wchar_t* pszUnicode = new wchar_t[iBufSize];

	MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

	pSurface->GetTextSize(font, pszUnicode, iWide, iTall);

	delete[] pszUnicode;

	return iWide;
}

void Draw::DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	CHAR szBuffer[MAX_PATH];

	if (!input)
		return;

	vsprintf_s(szBuffer, input, (char*)&input + _INTSIZEOF(input));

	if (center)
		x -= getWidht(font, szBuffer) / 2;

	pSurface->DrawSetTextColor(r, g, b, a);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextPos(x, y);
	std::wstring wide = stringToWide(std::string(szBuffer));
	pSurface->DrawPrintText(wide.c_str(), wide.length());
}

bool Draw::WorldToScreen(const Vector &vOrigin, Vector &vScreen)
{
	return (pDebugOverlay->ScreenPosition(vOrigin, vScreen) != 1);
}
