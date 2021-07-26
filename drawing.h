#pragma once


typedef unsigned long HFont;

namespace Fonts
{
	extern HFont m_MenuFont;
	extern HFont m_ListItemFont;
	extern HFont m_WatermarkFont;
	extern HFont m_VelocityFont;
}

namespace Draw
{
	VOID InitFonts();
	void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	bool WorldToScreen(const Vector &vOrigin, Vector &vScreen);
	INT getWidht(unsigned long font, const char* input);
	std::wstring stringToWide(const std::string& text);
	VOID DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...);
	void DrawTexts(unsigned long font, int x, int y, int r, int g, int b, int a, const wchar_t * text);
	void DrawMonitorBar(int x, int y, int cur, const char * title);
	void OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a);
	void SoftOutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a);
}

