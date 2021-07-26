#include "hooks.h"


cMenu g_Menu(400,200,290,253);

bool bSliderFix[50];

int iSliderIndex = -1;
int iCurrSlider;

DWORD dwWait;

#define COLOR1 60, 60, 60, 255
#define COLOR2 85, 85, 85, 255
#define COLOR3 0, 0, 0, 255
#define COLOR4 35, 35, 35, 255
#define COLOR5 50, 50, 50, 255
#define COLOR6 100, 100, 100, 255
#define COLOR7 73, 73, 73, 255
#define COLOR8 65, 65, 65, 255

#define COLOR9 (gCvars.espcolor[0]), (gCvars.espcolor[1]), (gCvars.espcolor[2]), 255

#define LISTITEM_TEXTCOLOR 255, 255, 255, 255

#define ELEMENT_SEPERATION 20
#define CHECKBOX_SEPERATION_FROM_TEXT 100
#define CHECKBOX_SIZE 13

#define DEFAULT_X_TO_ADD (70 + CHECKBOX_SIZE + 40)

#define DROPDOWN_WIDTH 57
#define DROPDOWN_HEIGHT 15

#define ADDER_SIZE 12
#define ADDER_SEPERATE_FROM_BOXES 44 

cMenu::cMenu(int x, int y, int w, int h)
{
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
}

char *fuckingkeynames[] = { "M2","F","Z","Q","V" };
float fuckingkeyvalues[] = { 0x02,0x46,0x5A,0x51,0x56 };

void cMenu::InitMenuElements()
{
	static cMenuSection msAimbot;
	static cMenuSection msAimbotSliders;
	static cMenuSection radarslider;
	static cMenuSection msEsp;
	static cMenuSection msMisc;
	static cMenuSection msRemovals;
	static cMenuSection msskinss;
	static cMenuSection hoodrich;

	int iRowTwo = DEFAULT_X_TO_ADD;

	int iUsualX = m_x + 10;

	iCurrSlider = 0;

	switch (GetTabIndex())
	{
	case AIMTAB:

		msAimbot.ClearSection();
		msAimbotSliders.ClearSection();

		msAimbot.Draw(iUsualX, m_y + 30, m_w - 22, 80);

		msAimbot.AddElement(ONOFF, -3, L" AIM ENABLE", &gCvars.ENABLEAIM);
		msAimbot.AddElement(ONOFF, -3, L" AIM ON FIRE", &gCvars.AIMONFIRE);
		msAimbot.AddElement(ONOFF, -3, L" SILENT AIM", &gCvars.SILENTAIM);

		msAimbot.RestartSection();

		msAimbot.AddElement(ONOFF, iRowTwo, L"        NORECOIL", &gCvars.NORECOIL);
		msAimbot.AddElement(ONOFF, iRowTwo, L"        NOSPREAD", &gCvars.NOSPREAD);
		msAimbot.AddElement(ONOFF, iRowTwo, L"        AUTOFIRE", &gCvars.AUTOFIRE);

		msAimbotSliders.Draw(iUsualX, m_y + 116, m_w - 22, 124);

		msAimbotSliders.SetSlider(iCurrSlider, true);
		msAimbotSliders.AddElement(SLIDER, 0, L"TARGET SELECTION FOV", &gCvars.AIMFOV, 0, 180);
		msAimbotSliders.SetSlider(iCurrSlider, true);
		msAimbotSliders.AddElement(SLIDER, 0, L"SMOOTHNESS PITCH", &gCvars.SMOOTHPITCH, 0, 255);
		msAimbotSliders.SetSlider(iCurrSlider, true);
		msAimbotSliders.AddElement(SLIDER, 0, L"SMOOTHNESS YAW", &gCvars.SMOOTHYAW, 0, 255);

		break;

	case ESPTAB:

		msEsp.ClearSection();
		radarslider.ClearSection();

		msEsp.Draw(iUsualX, m_y + 30, m_w - 22, 80);

		msEsp.AddElement(ONOFF, 0, L"ESP NAME", &gCvars.ESPNAME);
		msEsp.AddElement(ONOFF, 0, L"ESP BOX", &gCvars.ESPBOX);
		msEsp.AddElement(ONOFF, 0, L"ESP HEALTH", &gCvars.ESPHEALTH);
		msEsp.RestartSection();
		msEsp.AddElement(ONOFF, iRowTwo, L"        CHAMS", &gCvars.CHAMS);
		msEsp.AddElement(ONOFF, iRowTwo, L"        CHAM XQZ", &gCvars.CHAMSXQZ);
		msEsp.AddElement(ONOFF, iRowTwo, L"        CHAM HAND", &gCvars.CHAMHAND);

		radarslider.Draw(iUsualX, m_y + 116, m_w - 22, 124);

		radarslider.SetSlider(iCurrSlider, true);
		radarslider.AddElement(SLIDER, 0, L"RED", &gCvars.espcolor[0], 0, 255);
		radarslider.SetSlider(iCurrSlider, true);
		radarslider.AddElement(SLIDER, 0, L"GREEN", &gCvars.espcolor[1], 0, 255);
		radarslider.SetSlider(iCurrSlider, true);
		radarslider.AddElement(SLIDER, 0, L"BLUE", &gCvars.espcolor[2], 0, 255);

		break;

	case MISCTAB:

		msRemovals.ClearSection();
		msskinss.ClearSection();
		hoodrich.ClearSection();

		hoodrich.Draw(iUsualX, m_y + 30, m_w - 22, 64);
		hoodrich.SetValueNames(fuckingkeynames, fuckingkeyvalues, 5);
		hoodrich.AddElement(ADDER, -20, L"      SEQUENCE", &gCvars.LAGFAST, 0, 1000);
		hoodrich.AddElement(DROPDOWN, -20, L"      KEYBIND", &gCvars.LAGKEY);
		hoodrich.RestartSection();
		hoodrich.SetValueNames(fuckingkeynames, fuckingkeyvalues, 5);
		hoodrich.AddElement(ADDER, iRowTwo -14, L"      OVERSPED", &gCvars.SPEEDFAST, 0, 10);
		hoodrich.AddElement(DROPDOWN, iRowTwo -14, L"      KEYBIND", &gCvars.SPEEDKEY);


		msRemovals.Draw(iUsualX, m_y + 100, m_w - 175, 140);
		msRemovals.AddElement(ONOFF, -17, L"     BUNNYHOP", &gCvars.AUTOBH);
		msRemovals.AddElement(ONOFF, -17, L"     VELOCITY", &gCvars.velocity);
		msRemovals.AddElement(ONOFF, -17, L"     RADAR", &gCvars.radar);
		msRemovals.AddElement(ONOFF, -17, L"     WATERMARK", &gCvars.watermark);
		msRemovals.AddElement(ONOFF, -17, L"     NO VOMIT", &gCvars.NOVOMIT);
		msRemovals.AddElement(ONOFF, -17, L"     MONITOR", &gCvars.drawmonitor);

		msskinss.Draw(iUsualX + 120, m_y + 100, m_w - 142, 140);

		msskinss.AddElement(ONOFF, -9, L"   TRIGGERBOT", &gCvars.trigenable);
		msskinss.AddElement(ONOFF, -9, L"   TRIG HEAD", &gCvars.trighead);
		msskinss.AddElement(ONOFF, -9, L"   TRIG BODY", &gCvars.triggerbody);
		msskinss.AddElement(ONOFF, -9, L"   TRIG LIMB", &gCvars.TRIGLIMB);
		msskinss.SetValueNames(fuckingkeynames, fuckingkeyvalues, 5);
		msskinss.AddElement(DROPDOWN, -10, L"    KEY BIND", &gCvars.triggerkey);
		msskinss.AddElement(ADDER, -10, L"    DELAY", &gCvars.trigerdelay, 1, 150);

		hoodrich.PostSection();
		msskinss.PostSection();
		msRemovals.PostSection();
		break;
	}
}

int iNubLoop[] = {22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

void cMenu::DrawTab(int index, int &setindex, int x, int y, const char *pszTitle)
{
	static int iWidth = 90;
	static int iHeight = 22;

	bool bOverTri = false;

	bool bOverBack = g_Mouse.IsOver(x + iHeight, y - iHeight, iWidth + 1 - iHeight, iHeight + 1);

	bool bSame = setindex == index;

	for (int ax = 0; ax <= iHeight; ax++)
	{
		if (g_Mouse.IsOver(x + ax, y - ax, 2, ax) || g_Mouse.IsOver(x + iWidth + ax, y - iHeight, 2, iNubLoop[ax]))
		{
			bOverTri = true;
			break;
		}
	}

	for (int i = 0; i <= iHeight; i++)
	{
		if (bSame)
		{
			pSurface->DrawSetColor(COLOR7);

			pSurface->DrawLine(x + i, y, x + iHeight + i, y - iHeight);
			pSurface->DrawLine(x + iWidth + iHeight - i, y - iHeight, x + iWidth - i, y);

			if (i == iHeight)
				Draw::FillRGBA(x + iHeight, y - iHeight, iWidth - iHeight, iHeight + 1, COLOR7);
		}
		else
		{
			if (bOverBack || bOverTri)
				pSurface->DrawSetColor(COLOR8);
			else
				pSurface->DrawSetColor(COLOR1);

			pSurface->DrawLine(x + i, y, x + iHeight + i, y - iHeight);
			pSurface->DrawLine(x + iWidth + iHeight - i, y - iHeight, x + iWidth - i, y);

			if (g_Mouse.HasMouseOneJustBeenReleased() && (bOverBack || bOverTri))
				setindex = index;

			if (i == iHeight)
			{
				if (bOverBack || bOverTri)
					Draw::FillRGBA(x + iHeight, y - iHeight, iWidth - iHeight, iHeight + 1, COLOR8);
				else
					Draw::FillRGBA(x + iHeight, y - iHeight, iWidth - iHeight, iHeight + 1, COLOR1);
			}
		}
	}

	pSurface->DrawSetColor(COLOR2);

	pSurface->DrawLine(x, y, x + iHeight, y - iHeight);
	pSurface->DrawLine(x + iHeight, y - iHeight, x + iWidth + iHeight + 1, y - iHeight);
	pSurface->DrawLine(x + iWidth, y, x + iWidth + iHeight, y - iHeight);
	pSurface->DrawLine(x, y, x + iWidth, y);
	Draw::DrawStringA(Fonts::m_WatermarkFont, true, x + (iWidth + iHeight) * 0.5, y + 1 - iHeight, COLOR9, pszTitle);
}

void cMenu::DrawMenu()
{
	Draw::FillRGBA(m_x + 22, m_y - 22, 80 * NUM_OF_TABS + 20, 23, COLOR4);

	pSurface->DrawSetColor(COLOR1);

	DrawTab(AIMTAB, iTabIndex, m_x, m_y, "AIM");
	DrawTab(ESPTAB, iTabIndex, m_x + 100, m_y, "VISUALS");
	DrawTab(MISCTAB, iTabIndex, m_x + 200, m_y, "MISC");

	Draw::FillRGBA(m_x, m_y + 1, m_w, m_h, COLOR3);
	Draw::FillRGBA(m_x + 1, m_y + 2, m_w - 2, m_h - 2, COLOR4);
	Draw::FillRGBA(m_x + 6, m_y + 7, m_w - 12, m_h - 12, COLOR3);
	Draw::FillRGBA(m_x + 7, m_y + 8, m_w - 14, m_h - 14, COLOR5);
	Draw::FillRGBA(m_x + 5, m_y + 6, m_w - 10, 17, COLOR3);
	Draw::FillRGBA(m_x + 5, m_y + 7, m_w - 10, 15, COLOR5);

    #define BUILDSTAMP ( L"BINARY BUILD DATE: " __DATE__ L" @ " __TIME__ )
	Draw::DrawTexts(Fonts::m_MenuFont, m_x + 15, m_y + 7, COLOR9, BUILDSTAMP);

	Draw::FillRGBA(m_x - 15, m_y + 95, 15, 55, COLOR3);

	if (g_Mouse.OneLeftClick(m_x - 14, m_y + 96, 14, 53)) //LOAD CFG
	{
		Config->Save();
	}

	if (g_Mouse.LeftClick(m_x - 14, m_y + 96, 14, 53))
		Draw::FillRGBA(m_x - 15, m_y + 95, 15, 55, COLOR9);

	Draw::FillRGBA(m_x - 14, m_y + 96, 14, 53, COLOR6);
	Draw::DrawTexts(Fonts::m_MenuFont, m_x - 10, m_y + 95, COLOR9, L"S");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x - 10, m_y + 107, COLOR9, L"A");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x - 10, m_y + 119, COLOR9, L"V");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x - 10, m_y + 131, COLOR9, L"E");


	Draw::FillRGBA(m_x + m_w, m_y + 95, 15, 55, COLOR3);

	if (g_Mouse.OneLeftClick(m_x + m_w, m_y + 96, 14, 53)) //SAVE CFG
	{
		Config->Load();
	}

	if (g_Mouse.LeftClick(m_x + m_w, m_y + 96, 15, 55))
		Draw::FillRGBA(m_x + m_w, m_y + 95, 15, 55, COLOR9);

	Draw::FillRGBA(m_x + m_w, m_y + 96, 14, 53, COLOR6);

	Draw::DrawTexts(Fonts::m_MenuFont, m_x + m_w + 3, m_y + 95, COLOR9, L"L");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x + m_w + 3, m_y + 107, COLOR9, L"O");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x + m_w + 3, m_y + 119, COLOR9, L"A");
	Draw::DrawTexts(Fonts::m_MenuFont, m_x + m_w + 3, m_y + 131, COLOR9, L"D");

	InitMenuElements();
}

void cMenuSection::Draw(int x, int y, int w, int h)
{
	Draw::FillRGBA(x,y,10,1,COLOR2);
	Draw::FillRGBA(x,y,1,h,COLOR2);
	Draw::FillRGBA(x,y+h,w,1,COLOR2);
	Draw::FillRGBA(x+w,y,1,h+1,COLOR2);
	Draw::FillRGBA(x, y, w, 1, COLOR2);

	SetSectionPos(x,y);
}

void cMenuSection::DrawAllDropDowns()
{
	int iNumOfDropDowns = vecDropDowns.size();

	int iWhich = -1;

	for(int i2 = (iNumOfDropDowns - 1); i2 >= 0; i2--)
	{
		bool bIsActive = bActiveDropDown[i2];

		if(bIsActive)
		{
			iWhich = i2;

			dwWait = GetTickCount() + 700;
			break;
		}
	}

	for(int i = (iNumOfDropDowns - 1); i >= 0; i--)
	{
		int e_x = vecDropDowns[i].x;
		int e_y = vecDropDowns[i].y;
		int iCount = vecDropDowns[i].iCount;

		bool bIsActive = bActiveDropDown[i];

		char **ppszNames = vecDropDowns[i].ppszNames;
		float *fValues  = vecDropDowns[i].fValues;
		float *cvar = vecDropDowns[i].cvar;

		if(bIsActive)
		{
			int string_x = e_x + (DROPDOWN_WIDTH * 0.5);

			for(int ax = 0; ax < iCount; ax++)
			{
				if(g_Mouse.IsOver(e_x,e_y + (ax * DROPDOWN_HEIGHT),DROPDOWN_WIDTH,DROPDOWN_HEIGHT))
				{
					if(!g_Menu.IsHandlingItem())
						g_Menu.AddMenuFlag(FL_DISABLEDRAG);

					Draw::FillRGBA(e_x + 1,e_y + 1 + (ax * DROPDOWN_HEIGHT),DROPDOWN_WIDTH - 1,DROPDOWN_HEIGHT - (ax == (iCount - 1) ? 1 : 0),COLOR5);
					
					if(g_Mouse.HasMouseOneJustBeenReleased())
					{
						*cvar = fValues[ax];

						bActiveDropDown[i] = false;
					}
				}
				else
				{
					Draw::FillRGBA(e_x + 1,e_y + 1 + (ax * DROPDOWN_HEIGHT),DROPDOWN_WIDTH - 1,DROPDOWN_HEIGHT - (ax == (iCount - 1) ? 1 : 0),COLOR4);
				
					if(g_Mouse.HasMouseOneJustBeenReleased())
					{
						bActiveDropDown[i] = false;
					}
				}

				if(ax == (iCount - 1))
					Draw::SoftOutlinedRectangle(e_x,e_y,DROPDOWN_WIDTH,(ax + 1) * DROPDOWN_HEIGHT,COLOR3);

				if(*cvar == fValues[ax])
					Draw::DrawStringA(Fonts::m_ListItemFont,true,string_x,e_y + (ax * DROPDOWN_HEIGHT),COLOR9,ppszNames[ax]);
				else
					Draw::DrawStringA(Fonts::m_ListItemFont,true,string_x,e_y + (ax * DROPDOWN_HEIGHT),LISTITEM_TEXTCOLOR,ppszNames[ax]);
			}
		}
		else
		{
			if(g_Mouse.IsOver(e_x,e_y,DROPDOWN_WIDTH,DROPDOWN_HEIGHT))
			{
				if(!g_Menu.IsHandlingItem())
					g_Menu.AddMenuFlag(FL_DISABLEDRAG);

				Draw::FillRGBA(e_x + 1,e_y + 1,DROPDOWN_WIDTH - 1,DROPDOWN_HEIGHT - 1,COLOR5);

				if(g_Mouse.HasMouseOneJustBeenReleased() && (dwWait < GetTickCount() || iWhich == -1))
				{
					bActiveDropDown[i] = true;
				}
			}
			else
				Draw::FillRGBA(e_x + 1,e_y + 1,DROPDOWN_WIDTH - 1,DROPDOWN_HEIGHT - 1,COLOR4);

			Draw::SoftOutlinedRectangle(e_x,e_y,DROPDOWN_WIDTH,DROPDOWN_HEIGHT,COLOR3);

			int string_x = e_x + (DROPDOWN_WIDTH * 0.5);
			int string_y = e_y;

			for(int ax = 0; ax < iCount; ax++)
			{
				if(*cvar == fValues[ax])
				{
					Draw::DrawStringA(Fonts::m_ListItemFont,true,string_x,string_y,LISTITEM_TEXTCOLOR,ppszNames[ax]);
					break;
				}
			}
		}
	}

	ClearAllElementSpecifics();
}

void cMenuSection::AddElement(int iType, int add_to_x, const wchar_t *pszElementName, float *cvar, float min, float max, float step)
{
	int e_x = s_x + 10 + add_to_x;
	int e_y = s_y + 15 + (iSection * ELEMENT_SEPERATION);

	bool bDropDownActive = false;

	for (int i2 = 0; i2 < 50; i2++)
	{
		bDropDownActive = bActiveDropDown[i2];

		if (bDropDownActive)
			break;
	}

	if (iType == ONOFF)
	{
		Draw::DrawTexts(Fonts::m_WatermarkFont, e_x, e_y, LISTITEM_TEXTCOLOR, pszElementName);

		e_x += CHECKBOX_SEPERATION_FROM_TEXT;

		if (g_Mouse.OneLeftClick(e_x - 3, e_y - 3, CHECKBOX_SIZE + 5, CHECKBOX_SIZE + 5) && !bDropDownActive)
			*cvar = !*cvar;

		e_y += 1;

		Draw::FillRGBA(e_x, e_y, CHECKBOX_SIZE, CHECKBOX_SIZE, COLOR7);

		if (*cvar)
		{
			pSurface->DrawSetColor(COLOR4);

			pSurface->DrawLine(e_x + 2, e_y + 2, e_x + CHECKBOX_SIZE - 1, e_y + CHECKBOX_SIZE - 1);
			pSurface->DrawLine(e_x + CHECKBOX_SIZE - 2, e_y + 2, e_x + 1, e_y + CHECKBOX_SIZE - 1);
		}

		if (g_Mouse.IsOver(e_x, e_y, CHECKBOX_SIZE, CHECKBOX_SIZE))
		{
			Draw::OutlinedRectangle(e_x, e_y, CHECKBOX_SIZE, CHECKBOX_SIZE, COLOR9);

			if (!g_Menu.IsHandlingItem())
				g_Menu.AddMenuFlag(FL_DISABLEDRAG);
		}
		else
			Draw::OutlinedRectangle(e_x, e_y, CHECKBOX_SIZE, CHECKBOX_SIZE, COLOR4);
	}
	else if (iType == DROPDOWN)
	{
		Draw::DrawTexts(Fonts::m_WatermarkFont, e_x, e_y, LISTITEM_TEXTCOLOR, pszElementName);

		e_y += 1;

		DropDown_t ddNew;

		ddNew.x = e_x + CHECKBOX_SEPERATION_FROM_TEXT - 20;
		ddNew.y = e_y - 2;
		ddNew.fValues = fValueList;
		ddNew.cvar = cvar;
		ddNew.ppszNames = ppszValueNames;
		ddNew.iCount = iValueCount;

		AddDropDownToDrawList(ddNew);
	}
	else if (iType == SLIDER)
	{
		float Scale = max / 245;

		bool bOver = false;


		wchar_t szCopy[256];

		wcscpy_s(szCopy, pszElementName);
		swprintf_s(szCopy, L"%s %2.2f", pszElementName, *cvar);

		Draw::DrawTexts(Fonts::m_WatermarkFont, e_x, e_y - 7, LISTITEM_TEXTCOLOR, szCopy);


		e_y += 8;

		Draw::FillRGBA(e_x + 3, e_y + 7, 240, 1, 115, 120, 123, 185);

		int mouse_x, mouse_y;
		g_Mouse.GetMousePosition(mouse_x, mouse_y);

		if (mouse_x >= (e_x - 3) && mouse_x <= (e_x + fLength + 3) && mouse_y >= (e_y) && mouse_y <= (e_y + 10) && GetAsyncKeyState(VK_LBUTTON) && (iSliderIndex == -1) && dwWait < GetTickCount() && !bSliderFix[iCurrSlider])
		{
			iSliderIndex = iCurrSlider;
			bSliderFix[iCurrSlider] = true;

			if (!g_Menu.IsHandlingItem())
				g_Menu.AddMenuFlag(FL_DISABLEDRAG);
		}

		if (mouse_x >= (e_x - 1000) && mouse_x <= (e_x + fLength + 1000) && mouse_y >= (e_y - 1000) && mouse_y <= (e_y + 1000) && GetAsyncKeyState(VK_LBUTTON) && !bDropDownActive)
		{
			if (bSliderFix[iCurrSlider])
			{
				*cvar = min + (mouse_x - e_x) * Scale;

				bOver = true;

				if (!g_Menu.IsHandlingItem())
					g_Menu.AddMenuFlag(FL_DISABLEDRAG);
			}
		}
		else if (bSliderFix[iCurrSlider])
		{
			iSliderIndex = -1;
			bSliderFix[iCurrSlider] = false;
		}

		if (*cvar > max)
			*cvar = max;

		if (*cvar < min)
			*cvar = min;

		static int iSizeOf = 6;

		for (int nu = 0; nu <= iSizeOf; nu++)
		{
			Draw::FillRGBA(e_x + (*cvar / Scale) - iSizeOf + nu, e_y + iSizeOf - nu, (iSizeOf + 1) - nu, 1, COLOR4);
			Draw::FillRGBA(e_x + (*cvar / Scale) - iSizeOf + nu, e_y + iSizeOf + nu, (iSizeOf + 1) - nu, 1, COLOR4);

			Draw::FillRGBA(e_x + (*cvar / Scale), e_y + iSizeOf - nu, (iSizeOf + 1) - nu, 1, COLOR4);
			Draw::FillRGBA(e_x + (*cvar / Scale), e_y + iSizeOf + nu, (iSizeOf + 1) - nu, 1, COLOR4);
		}

		if (g_Mouse.IsOver(e_x + (*cvar / Scale) - iSizeOf, e_y - 1, 10, 14) || bOver)
			pSurface->DrawSetColor(COLOR9);
		else
			pSurface->DrawSetColor(COLOR6);

		pSurface->DrawLine(e_x + (*cvar / Scale) - (iSizeOf + 1), e_y + iSizeOf, e_x + (*cvar / Scale), e_y - 1);
		pSurface->DrawLine(e_x + (*cvar / Scale), e_y - 1, e_x + (*cvar / Scale) + (iSizeOf + 1), e_y + iSizeOf);
		pSurface->DrawLine(e_x + (*cvar / Scale) + (iSizeOf + 1), e_y + iSizeOf, e_x + (*cvar / Scale), e_y + (iSizeOf * 2 + 1));
		pSurface->DrawLine(e_x + (*cvar / Scale), e_y + (iSizeOf * 2 + 1), e_x + (*cvar / Scale) - (iSizeOf + 1), e_y + iSizeOf);
	}
	else if (iType == ADDER)
	{

	    Draw::DrawTexts(Fonts::m_WatermarkFont, e_x, e_y, LISTITEM_TEXTCOLOR, pszElementName);

		e_y += 1;

		e_x += (CHECKBOX_SEPERATION_FROM_TEXT - 20);

		Draw::FillRGBA(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR7);

		if (g_Mouse.IsOver(e_x, e_y, ADDER_SIZE, ADDER_SIZE))
		{
			Draw::OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR9);

			if (g_Mouse.HasMouseOneJustBeenReleased() && !bDropDownActive)
				*cvar -= step;

			if (g_Mouse.IsMouseTwoBeingHeld() && !bDropDownActive)
				*cvar -= 1;
		}
		else
			Draw::OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR4);

		Draw::DrawStringA(Fonts::m_ListItemFont, true, e_x + ADDER_SIZE * 0.5, e_y - 1, COLOR9, "<");

		Draw::DrawStringA(Fonts::m_WatermarkFont, true, e_x - 6 + ADDER_SIZE + ADDER_SEPERATE_FROM_BOXES * 0.5, e_y - 2, LISTITEM_TEXTCOLOR, "%2.0f", *cvar);

		e_x += ADDER_SEPERATE_FROM_BOXES;

		Draw::FillRGBA(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR7);

		if (g_Mouse.IsOver(e_x, e_y, ADDER_SIZE, ADDER_SIZE))
		{
			Draw::OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR9);

			if (g_Mouse.HasMouseOneJustBeenReleased() && !bDropDownActive)
				*cvar += step;

			if (g_Mouse.IsMouseTwoBeingHeld() && !bDropDownActive)
				*cvar += 1;
		}
		else
			Draw::OutlinedRectangle(e_x, e_y, ADDER_SIZE, ADDER_SIZE, COLOR4);


		Draw::DrawStringA(Fonts::m_ListItemFont, true, e_x + ADDER_SIZE * 0.5, e_y - 1, COLOR9, ">");

		//clamp but go to min,max instead of not allowing to increase/decrease
		if (*cvar < min)
			*cvar = max;

		if (*cvar > max)
			*cvar = min;
	}

	PostElement((iType == SLIDER ? 2 : 1));
}