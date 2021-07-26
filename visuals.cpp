#include "hooks.h"

#define COLORESP (gCvars.espcolor[0]), (gCvars.espcolor[1]), (gCvars.espcolor[2]), 255

void ESP::DrawMonitor(int x, int y, CBaseEntity * entity)
{
	int sizex = 50;
	int sizey = 100;

	if (g_Mouse.LeftClick(gCvars.f1monitorpos_x - (sizex / 2) - 6, gCvars.f1monitorpos_y - (sizey / 2) - 6, sizex * 2 + 12, sizey * 2 + 12))
	{
		gCvars.f1monitorpos_x = g_Mouse.mouse_x;
		gCvars.f1monitorpos_y = g_Mouse.mouse_y;
		gCvars.f1monitorpos_x = gCvars.f1monitorpos_x;
		gCvars.f1monitorpos_y = gCvars.f1monitorpos_y;
	}

	int centerx = gCvars.f1monitorpos_x + (sizex / 2);
	int centery = gCvars.f1monitorpos_y + (sizey / 2);

	Draw::FillRGBA(centerx - sizex - 6, centery - sizey - 20, 2 * sizex + 12, 2 * sizey + 26, 35, 35, 35, 255);
	Draw::OutlinedRectangle(centerx - sizex - 6, centery - sizey - 20, 2 * sizex + 12, 2 * sizey + 26, 0, 0, 0, 254);

	Draw::DrawStringA(Fonts::m_MenuFont, false, centerx - sizex, centery - sizey - 19, 255, 255, 255, 255, "Monitor");
	Draw::FillRGBA(centerx - sizex, centery - sizey, 2 * sizex, 2 * sizey, 50, 50, 50, 255);

	Draw::OutlinedRectangle(centerx - sizex, centery - sizey, 2 * sizex, 2 * sizey, 0, 0, 0, 254);

	int iSpeed = 0;
	float flPunch = 0.0f;

	Vector vSpeed = entity->GetVelocity();
	iSpeed = (int)vSpeed.Length2D();

	Vector pAngle = entity->GetPunchAngle();
	float flModifier = pAngle.Normalize();

	flModifier -= (10.0f + flModifier * 0.5f) * pGlobalvars->interval_per_tick;
	pAngle *= flModifier;
	flPunch = ((pAngle.x * 17.77777777777778) * 1.25);

	Draw::DrawMonitorBar(centerx - sizex + 9, centery - sizey + 12, (-flPunch), "Recoil");
	Draw::DrawMonitorBar(centerx - sizex + 59, centery - sizey + 12, (iSpeed * 0.2), "Speed");
}

RECT ESP::DynamicBox(CBaseEntity* pPlayer, bool& PVS, CBaseEntity* local)
{
	Vector trans = pPlayer->GetAbsOrigin();

	Vector min;
	Vector max;

	min = pPlayer->GetMins();
	max = pPlayer->GetMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	Math::CalcAngle(trans, local->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		Math::angleVectors(angs,all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!Draw::WorldToScreen(all[3], flb))
		PVS = false;
	if (!Draw::WorldToScreen(all[0], blb))
		PVS = false;
	if (!Draw::WorldToScreen(all[2], frb))
		PVS = false;
	if (!Draw::WorldToScreen(all[6], blt))
		PVS = false;
	if (!Draw::WorldToScreen(all[5], brt))
		PVS = false;
	if (!Draw::WorldToScreen(all[4], frt))
		PVS = false;
	if (!Draw::WorldToScreen(all[1], brb))
		PVS = false;
	if (!Draw::WorldToScreen(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;
	return rect;
}


void ESP::drawvelocity(int screenWidth, int screenHeight, CBaseEntity* local_player)
{
	Vector speed = local_player->GetVelocity();

	int intspeed = round(speed.Length2D());

	char vel[256];

	sprintf_s(vel, "%d", intspeed);

	Draw::DrawStringA(Fonts::m_VelocityFont, true, screenWidth / 2, screenHeight - 100, COLORESP, vel);
}

void ESP::drawradar(int screenwidght, int screenhight, CBaseEntity* local)
{
	for (int ax = 1; ax <= pEntList->GetHighestEntityIndex(); ax++)
	{
		CBaseEntity * pEntity = pEntList->GetClientEntity(ax);

		if (!pEntity || pEntity == local || pEntity->IsDormant())
			continue;

		if (!pEntity->GetModel())
			continue;

		if (pEntity->GetTeamNum() == TEAM_SURVIVOR)
			continue;

		std::int32_t nClassID = pEntity->GetClientClass()->GetClassID;

		if (!pEntity->GetGroup() && !pEntity->ValidEntity())
			continue;

		static Vector vClientViewAngles;

		pEngine->GetViewAngles(vClientViewAngles);

		DrawRadarPoint(pEntity->GetAbsOrigin(), local->GetAbsOrigin(), vClientViewAngles);
	}
}

void ESP::DrawRadarBack(int screenwidght, int screenhight)
{
	bool bSave_Radar_Pos = true;

	int size = 110;
	size -= 10;

	if (g_Mouse.LeftClick(gCvars.flRadarPos_x - (size / 2) - 6, gCvars.flRadarPos_y - (size / 2) - 6, size * 2 + 12, size * 2 + 12))
	{
		if (!bSave_Radar_Pos)
		{
			gCvars.iSavedRadarX = g_Mouse.mouse_x - gCvars.flRadarPos_x;
			gCvars.iSavedRadarY = g_Mouse.mouse_y - gCvars.flRadarPos_y;
			bSave_Radar_Pos = true;
		}
		gCvars.flRadarPos_x = g_Mouse.mouse_x;
		gCvars.flRadarPos_y = g_Mouse.mouse_y;
		gCvars.flRadarPos_x = gCvars.flRadarPos_x - gCvars.iSavedRadarX;
		gCvars.flRadarPos_y = gCvars.flRadarPos_y - gCvars.iSavedRadarY;
	}
	else
	{
		bSave_Radar_Pos = false;
	}

	int centerx = gCvars.flRadarPos_x + (size / 2);
	int centery = gCvars.flRadarPos_y + (size / 2);

	Draw::FillRGBA(centerx - size - 6, centery - size - 20, 2 * size + 12, 2 * size + 26, 35, 35, 35, 255);
	Draw::OutlinedRectangle(centerx - size - 6, centery - size - 20, 2 * size + 12, 2 * size + 26, 0, 0, 0, 254);

	Draw::DrawStringA(Fonts::m_MenuFont, false, centerx - size, centery - size - 19, 255, 255, 255, 255, "Radar");
	Draw::FillRGBA(centerx - size, centery - size, 2 * size, 2 * size, 50, 50, 50, 255);

	Draw::OutlinedRectangle(centerx - size, centery - size, 2 * size, 2 * size, 0, 0, 0, 254);
	Draw::FillRGBA(centerx, centery - size, 1, 2 * size, 0, 0, 0, 120);
	Draw::FillRGBA(centerx - size, centery, 2 * size, 1, 0, 0, 0, 120);
}

void ESP::DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle)
{
	int size = 110;

	int centerx = gCvars.flRadarPos_x + (size / 2);
	int centery = gCvars.flRadarPos_y + (size / 2);

	float dx = vecOriginx.x - vecOriginy.x;
	float dy = vecOriginx.y - vecOriginy.y;
	float flAngle = vAngle.y;
	float yaw = (flAngle)* (PI / 180.0);
	float mainViewAngles_CosYaw = cos(yaw);
	float mainViewAngles_SinYaw = sin(yaw);
	float x = dy * (-mainViewAngles_CosYaw) + dx * mainViewAngles_SinYaw;
	float y = dx * (-mainViewAngles_CosYaw) - dy * mainViewAngles_SinYaw;
	float range = size * 30;
	if (fabs(x) > range || fabs(y) > range)
	{
		if (y > x)
		{
			if (y > -x) {
				x = range * x / y;
				y = range;
			}
			else {
				y = -range * y / x;
				x = -range;
			}
		}
		else {
			if (y > -x) {
				y = range * y / x;
				x = range;
			}
			else {
				x = -range * x / y;
				y = -range;
			}
		}
	}
	int ScreenX = centerx + int(x / range * float(size));
	int ScreenY = centery + int(y / range * float(size));
	size -= 10;
	int radar_menu_x = centerx;
	int radar_menu_y = centery;

	if (ScreenX < radar_menu_x - size)
		ScreenX = radar_menu_x - size + 1;
	else if (ScreenX > radar_menu_x + size)
		ScreenX = radar_menu_x + size - 3;

	if (ScreenY < radar_menu_y - size)
		ScreenY = radar_menu_y - size + 2;
	else if (ScreenY > radar_menu_y + size)
		ScreenY = radar_menu_y + size - 4;

	Draw::FillRGBA(ScreenX - 1, ScreenY - 1, 4, 4, 255, 255, 255, 255);
}

void ESP::draw(CBaseEntity* pLocal)
{
	Vector screen, worldpos;

	int iMyTeam = pLocal->GetTeamNum();

	for (int i = 1; i <= pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity * pEntity = pEntList->GetClientEntity(i);

		if (!pEntity || pEntity == pLocal || pEntity->IsDormant())
			continue;

		if (!pEntity->GetModel())
			continue;

		int iTeamNum = pEntity->GetTeamNum();

		if (iTeamNum == iMyTeam)
			continue;

		if (pEntity->GetGroup() && pEntity->ValidEntity())
		{
			DrawPlayer(pEntity, pLocal);
		}
	}
}

void ESP::DrawBox(const RECT& rect)
{
	pSurface->DrawSetColor(COLORESP);
	pSurface->DrawOutlinedRect(rect.left, rect.top, rect.right, rect.bottom);
	pSurface->DrawSetColor(0,0,0,255);
	pSurface->DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1);
	pSurface->DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);
}


void ESP::DrawPlayer(CBaseEntity * pEntity, CBaseEntity * local)
{
	bool PVS = false;
	RECT rect = DynamicBox(pEntity, PVS, local);

	if (gCvars.ESPBOX)
	{
		DrawBox(rect);
	}

	if (gCvars.ESPNAME || gCvars.ESPHEALTH)
	{
		int middle = ((rect.right - rect.left) / 2) + rect.left;

		char * szname{ pEntity->GetClientClass()->GetName };

		int inthealth = pEntity->GetHealth();

		char helfl[256];

		sprintf_s(helfl, "(%d)", inthealth);

		if (local->GetTeamNum() == TEAM_SURVIVOR)
		{
			if (pEntity->GetGroup() == GROUP_INFECTED)
			{
				if (gCvars.ESPNAME)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.top - 15, 255, 255, 255, 255, "zombie");
				}
			}

			if (pEntity->GetGroup() == GROUP_SPECIAL)
			{
				if (gCvars.ESPNAME)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.top - 15, 255, 255, 255, 255, szname);
				}

				if (gCvars.ESPHEALTH)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.bottom + 1, 255, 255, 255, 255, helfl);
				}
			}

			if (pEntity->GetGroup() == GROUP_TANK)
			{
				if (gCvars.ESPNAME)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.top - 15, 255, 255, 255, 255, "Tank");
				}

				if (gCvars.ESPHEALTH)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.bottom + 1, 255, 255, 255, 255, helfl);
				}
			}

			if (pEntity->GetGroup() == GROUP_BITCH)
			{
				if (gCvars.ESPNAME)
				{
					Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.top - 15, 255, 255, 255, 255, "Witch");
				}
			}
		}

		if (local->GetTeamNum() == TEAM_ZOMBY)
		{
			if (pEntity->GetGroup() == GROUP_PLAYER)
			{
				if (pEntity->GetTeamNum() == TEAM_SURVIVOR && pEntity->GetLifeState() == LIFE_ALIVE)
				{
					if (gCvars.ESPNAME)
					{
						Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.top - 15, 255, 255, 255, 255, "Survivor");
					}

					if (gCvars.ESPHEALTH)
					{
						Draw::DrawStringA(Fonts::m_MenuFont, true, middle, rect.bottom + 1, 255, 255, 255, 255, helfl);
					}
				}
			}
		}
	}
}