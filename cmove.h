#pragma once

#include "bhop.h"

void CreateMove(CUserCmd* cmd)
{
	CBaseEntity* pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (pLocal && pWeapon && pLocal->IsAlive())
	{
		if (gCvars.AUTOBH)
		{
			RunBhop(cmd, pLocal);
		}

		if (gCvars.LAGFAST > 0 && GetAsyncKeyState(gCvars.LAGKEY))
		{
			Sequence::RemoveConds(gCvars.LAGFAST);
		}

		if (pWeapon->HasAmmo())
		{
			Vector qOldAngle = cmd->viewangles;

			float fCurTime = pGlobalvars->interval_per_tick * (pLocal->GetTickBase() + 1);
			float fNextPrimary = pWeapon->GetNextPrimaryAttack();

			bool bCanFire = true;

			static bool bOldBullet;

			if ((fNextPrimary > fCurTime) || bOldBullet)
				bCanFire = false;

			if (!(fNextPrimary > fCurTime))
				bOldBullet = false;

			if (pLocal->GetTeamNum() == TEAM_SURVIVOR)
			{
				if (GetAsyncKeyState(gCvars.triggerkey))
				{
					g_Aimbot.triggerbot(cmd, pLocal);
				}

				if (gCvars.ENABLEAIM && pWeapon->IsAimWep())
				{
					if (gCvars.AIMONFIRE)
					{
						if ((cmd->buttons & IN_ATTACK))
						{
							g_Aimbot.Main(cmd, pLocal);
						}
					}
					else
					{
						if (bCanFire)
						{
							g_Aimbot.Main(cmd, pLocal);
						}
					}
				}

				if (gCvars.NORECOIL)
				{
					g_Aimbot.ApplyRecoil(pLocal, cmd->viewangles, -1.0f);
				}

				if (gCvars.NOSPREAD)
				{
					if ((cmd->buttons & IN_ATTACK))
					{
						g_Aimbot.ApplySpread(cmd->command_number, pLocal, cmd->viewangles, -1.0f);
					}
				}

				g_Aimbot.FixMovement(cmd, qOldAngle);
			}
		}
	}
}

template<typename T> inline T get_BP()
{
	__asm mov eax, ebp
}

template<typename T> inline T get_SI()
{
	__asm mov eax, esi
}

using SetViewAngleFn = void(__stdcall*)(Vector &);
SetViewAngleFn org_SetViewAngles = nullptr;

void __stdcall hooked_SetViewAngles(Vector &angles)
{
	CUserCmd* cmd = get_SI<CUserCmd*>();
	unsigned* sequence_number = (*get_BP<unsigned**>() + 2);

	org_SetViewAngles(angles);

	if (cmd && cmd->command_number == *sequence_number)
	{
		if (gCvars.SPEEDFAST > 0)
		{
			static int i = 0;

			if (gCvars.SPEEDFAST && GetAsyncKeyState(gCvars.SPEEDKEY) && i-- > 0)
				*(****get_BP<unsigned long*****>() + 1) -= 5;
			else
				i = gCvars.SPEEDFAST;
		}

		CreateMove(cmd);

		*sequence_number = cmd->command_number;
	}
}
