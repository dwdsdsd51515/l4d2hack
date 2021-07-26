#pragma once

bool bMenu = false;

using paint_traverse_t = void(__thiscall *)(void*, unsigned int, bool, bool);
paint_traverse_t painttraverse_original = nullptr;

void __fastcall hkPaintTraverse(void* pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	painttraverse_original(pPanels, vguiPanel, forceRepaint, allowForce);

	CBaseEntity* pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (!pLocal)//superior way of checking if we are ingame
	{
		static unsigned int FocusOverlayPanel = 0;

		static bool FoundPanel = false;

		if (!FoundPanel)
		{
			PCHAR szPanelName = (PCHAR)pPanel->GetName(vguiPanel);
			if (strstr(szPanelName, "MainMenu"))
			{
				FocusOverlayPanel = vguiPanel;

				FoundPanel = true;
			}
		}
		else if (FocusOverlayPanel == vguiPanel)
		{
			if (GetAsyncKeyState(VK_END) & 1)
				bMenu = !bMenu;

			if (gCvars.watermark)
			{
				Draw::DrawTexts(Fonts::m_MenuFont, 20, 20, 255, 255, 255, 255, L"INTERWEBZ");
			}

			if (bMenu)
			{
				g_Mouse.Update();

				int copy_x, copy_y;
				int copy_w, copy_h;

				g_Menu.GetMenuPos(copy_x, copy_y);
				g_Menu.GetMenuSize(copy_w, copy_h);

				g_Menu.DrawMenu();

				g_Mouse.Drag(g_Mouse.bDragged[0],
					!g_Menu.IsHandlingItem(),
					g_Mouse.LeftClick(copy_x, copy_y, copy_w, copy_h), copy_x, copy_y, g_Mouse.iDiffX[0], g_Mouse.iDiffY[0]);

				g_Menu.SetMenuPos(copy_x, copy_y);

				if (g_Menu.IsHandlingItem())
					g_Menu.RemoveMenuFlag(FL_DISABLEDRAG);
			}

			if (!pLocal)
			{
				FoundPanel = false;
			}
		}
	}

	if (pLocal)//WERE INGAME LOL
	{
		static unsigned int FocusOverlayPanel = 0;

		static bool FoundPanel = false;

		if (!FoundPanel)
		{
			PCHAR szPanelName = (PCHAR)pPanel->GetName(vguiPanel);
			if (strstr(szPanelName, "FocusOverlayPanel"))
			{
				FocusOverlayPanel = vguiPanel;

				FoundPanel = true;
			}
		}
		else if (FocusOverlayPanel == vguiPanel)
		{
			if (GetAsyncKeyState(VK_END) & 1)
				bMenu = !bMenu;

			int iScreenWidth, iScreenHeight;
			pEngine->GetScreenSize(iScreenWidth, iScreenHeight);

			if (gCvars.ESPBOX || gCvars.ESPNAME || gCvars.ESPHEALTH)
			{
				ESP::draw(pLocal);
			}

			if (gCvars.watermark)
			{
				Draw::DrawTexts(Fonts::m_MenuFont, 20, 20, 255, 255, 255, 255, L"INTERWEBZ");
			}

			if (gCvars.radar)
			{
				ESP::DrawRadarBack(iScreenWidth, iScreenHeight);
				ESP::drawradar(iScreenWidth, iScreenHeight, pLocal);
			}

			if (pLocal->IsAlive())
			{
				if (gCvars.velocity)
				{
					ESP::drawvelocity(iScreenWidth, iScreenHeight, pLocal);
				}

				if (gCvars.drawmonitor)
				{
					ESP::DrawMonitor(iScreenWidth, iScreenHeight, pLocal);
				}
			}

			pPanel->SetMouseInputEnabled(vguiPanel, bMenu);

			if (bMenu)
			{
				g_Mouse.Update();

				int copy_x, copy_y;
				int copy_w, copy_h;

				g_Menu.GetMenuPos(copy_x, copy_y);
				g_Menu.GetMenuSize(copy_w, copy_h);

				g_Menu.DrawMenu();

				g_Mouse.Drag(g_Mouse.bDragged[0],
					!g_Menu.IsHandlingItem(),
					g_Mouse.LeftClick(copy_x, copy_y, copy_w, copy_h), copy_x, copy_y, g_Mouse.iDiffX[0], g_Mouse.iDiffY[0]);

				g_Menu.SetMenuPos(copy_x, copy_y);

				if (g_Menu.IsHandlingItem())
					g_Menu.RemoveMenuFlag(FL_DISABLEDRAG);
			}

			if (pLocal)
			{
				FoundPanel = false;
			}
		}
	}
}
