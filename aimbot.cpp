#include "hooks.h"
#include "sigs.h"

Aimbot g_Aimbot;

bool shoot;
static int custom_delay = 0;

int Aimbot::GetAimBone(CBaseEntity* e)
{
	int bone = 0;

	if (e)
	{
		studiohdr* hdr = pModel->GetStudiomodel(e->GetModel());
		if (hdr)
		{
			for (int i = 0; i < hdr->GetHitboxCount(0); i++)
			{
				mstudiobbox* box = hdr->pHitboxSet(0)->pHitbox(i);
				if (box)
				{
					if (box->group == HITGROUP_HEAD)
					{
						bone = i;
					}
				}
			}
		}
	}

	return bone;
}

void Aimbot::triggerbot(CUserCmd *cmd, CBaseEntity* local)
{
	Vector ViewAngles = cmd->viewangles;

	Vector CrosshairForward;
	Math::angleVectors(ViewAngles,CrosshairForward);

	CrosshairForward *= 8192.0f;

	Vector TraceSource = local->GetEyePosition();
	Vector TraceDestination = TraceSource + CrosshairForward;

	raytrace raytrace(TraceSource, TraceDestination);
	traceclass Trace;
	tracefitlers Skip = local;

	pEngineTrace->TraceRay(raytrace, &Skip, &Trace);

	if (!Trace.pent)
		return;

	if (!Trace.pent->ValidEntity())
		return;

	if (Trace.pent->GetTeamNum() == TEAM_SURVIVOR)
		return;

	bool didHit = false;

	if ((gCvars.trighead && Trace.hitgroup == HITGROUP_HEAD)
		|| (gCvars.triggerbody && Trace.hitgroup == HITGROUP_CHEST)
		|| (gCvars.triggerbody && Trace.hitgroup == HITGROUP_STOMACH)
		|| (gCvars.TRIGLIMB && Trace.hitgroup == HITGROUP_LEFTARM)
		|| (gCvars.TRIGLIMB && Trace.hitgroup == HITGROUP_RIGHTARM)
		|| (gCvars.TRIGLIMB && Trace.hitgroup == HITGROUP_LEFTLEG)
		|| (gCvars.TRIGLIMB && Trace.hitgroup == HITGROUP_RIGHTLEG))
	{
		didHit = true;
	}

	if (gCvars.trigerdelay >= 1)
	{
		if (custom_delay >= gCvars.trigerdelay / 30)
		{
			if (didHit)
			{
				custom_delay = 0;
				shoot = true;
				cmd->buttons |= IN_ATTACK;
			}
		}
		else
		{
			custom_delay++;
		}
	}
}


bool Aimbot::GetHitboxpos(CBaseEntity* pLocal, CBaseEntity* Entitiy, Vector &vPos, int iHitBox, matrix3x4_t matrix[128])
{
	Vector vMax;
	Vector vMin;

	studiohdr* hdr = pModel->GetStudiomodel(Entitiy->GetModel());

	if (!hdr)
		return false;

	mstudiobbox* hitbox = hdr->pHitboxSet(0)->pHitbox(iHitBox);

	if (!hitbox)
		return false;

	Math::VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
	Math::VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);

	if (vMin.IsZero() || vMax.IsZero())
		return false;

	vPos = (vMin + vMax) * 0.5;

	if (IsVisible(vEyePos, vPos, pLocal,Entitiy))
		return true;

	return false;
}

bool Aimbot::IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pLocal, CBaseEntity* target)
{
	if (!pLocal)
		return false;

	if (!target)
		return false;

	raytrace raytrace(vecStart, vecEnd);
	traceclass trace;
	tracefitlers Skip = pLocal;

	pEngineTrace->TraceRay(raytrace, &Skip, &trace);

	if (trace.pent == target || trace.fraction == 1.f)
		return true;

	return false;
}

void Aimbot::Main(CUserCmd* pUserCmd, CBaseEntity* pLocal)
{
	int iMyTeam = pLocal->GetTeamNum();

	vEyePos = pLocal->GetEyePosition();

	static Vector vClientViewAngles;
	pEngine->GetViewAngles(vClientViewAngles);

	static Vector vAngle;
	Math::angleVectors(vClientViewAngles, vAngle);

	Reset();

	for (INT ax = 1; ax <= pEntList->GetHighestEntityIndex(); ax++)
	{
		CBaseEntity* entity = pEntList->GetClientEntity(ax);

		if (!entity || entity == pLocal || !entity->ValidEntity())
			continue;

		if (!entity->GetModel())
			continue;

		if (entity->GetTeamNum() == TEAM_SURVIVOR)
			continue;

		if (entity->GetTeamNum() == TEAM_IDK)
			continue;

		if (entity->IsDormant())
			continue;

		matrix3x4_t matrix[128];

		if (!entity->SetupBones(matrix))
			continue;

		int aim = GetAimBone(entity);

		if (!GetHitboxpos(pLocal, entity, vTarget, aim, matrix))
			continue;

		float fCurrFOV = Math::GetFov(vEyePos, vTarget, vAngle);

		if (fCurrFOV > gCvars.AIMFOV)
			continue;

		fCurrFOV = (Vector(vTarget - vEyePos).Length());

		if (fBestTarget < fCurrFOV)
			continue;

		fBestTarget = fCurrFOV;

		vFinal = vTarget;

		iTarget = ax;
	}

	if (HasTarget())
	{
		Math::CalcAngle(vEyePos, vFinal, pUserCmd->viewangles);

		if (gCvars.SMOOTHPITCH > 0 && gCvars.SMOOTHYAW > 0)
		{
			vClientViewAngles.x = Math::AngleNormalize(vClientViewAngles.x);
			vClientViewAngles.y = Math::AngleNormalize(vClientViewAngles.y);

			Vector qDelta = pUserCmd->viewangles - vClientViewAngles;

			qDelta.x = Math::AngleNormalize(qDelta.x);
			qDelta.y = Math::AngleNormalize(qDelta.y);

			pUserCmd->viewangles.x = vClientViewAngles.x + qDelta.x / (float)gCvars.SMOOTHPITCH;
			pUserCmd->viewangles.y = vClientViewAngles.y + qDelta.y / (float)gCvars.SMOOTHYAW;

			pUserCmd->viewangles.x = Math::AngleNormalize(pUserCmd->viewangles.x);
			pUserCmd->viewangles.y = Math::AngleNormalize(pUserCmd->viewangles.y);
		}

		if (!gCvars.SILENTAIM)
		{
			pEngine->SetViewAngles(pUserCmd->viewangles);
		}

		if (gCvars.AUTOFIRE)
		{
			pUserCmd->buttons |= IN_ATTACK;
		}
	}
}

void Aimbot::FixMovement(CUserCmd* c, Vector &qOld)
{
	Vector vMove(c->forwardmove, c->sidemove, c->upmove);
	float fSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y);
	static Vector qMove;
	Math::vectorAngles(vMove, qMove);

	float fYaw = DEG2RAD(c->viewangles.y - qOld.y + qMove.y);

	c->forwardmove = cos(fYaw) * fSpeed * 1;
	c->sidemove = sin(fYaw) * fSpeed;
}

void Aimbot::ApplyRecoil(CBaseEntity *plocal, Vector &angles, float factor)
{
	angles += plocal->GetPunchAngle() * factor;
}

void Aimbot::ApplySpread(int sequence_number, CBaseEntity *plocal, Vector &angles, float factor)
{
	auto w = reinterpret_cast<CBaseCombatWeapon*>(pEntList->GetClientEntityFromHandle(plocal->GetActiveWeaponHandle()));

	if (!w)
		return;

	int random_seed = MD5_PseudoRandom(sequence_number) & 0x7fffffff;

	static auto SharedRandomFloat = (float(*)(const char *, float, float, int))FindProlog(FindString(GetModuleHandle("client"), "SharedRandomFloat"));
	static int &r_random_seed = **(int **)FindPattern((void *)SharedRandomFloat, 0x100, ((const pattern *)"\x01\x01\x00\x00\x00\xA1"));

	r_random_seed = random_seed;

	float spread = w->GetWeaponSpread();

	angles.x += SharedRandomFloat("CTerrorGun::FireBullet HorizSpread", -spread, spread, 0) * factor;
	angles.y += SharedRandomFloat("CTerrorGun::FireBullet VertSpread", -spread, spread, 0) * factor;
}