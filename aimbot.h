

class Aimbot
{
public:
	void Main(CUserCmd* pUserCmd, CBaseEntity* pLocal);

	int GetAimBone(CBaseEntity* e);

	bool GetHitboxpos(CBaseEntity* pLocal, CBaseEntity* Entitiy, Vector &vPos, int iHitBox, matrix3x4_t matrix[128]);

	void ApplySpread(int sequence_number, CBaseEntity *plocal, Vector &angles, float factor);

	void FixMovement(CUserCmd* c, Vector &qOld);

	void ApplyRecoil(CBaseEntity *plocal, Vector &angles, float factor);

	bool IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pLocal, CBaseEntity* target);

	void triggerbot(CUserCmd *cmd, CBaseEntity* local);

	void Reset()
	{
		iTarget = -1;
		fBestTarget = 99999.9f;
		vTarget.Zero();
		vFinal.Zero();
	}

	bool HasTarget()
	{
		return (iTarget != -1);
	}

	int iTarget;
	float fBestTarget;
	Vector vTarget;
	Vector vFinal;
	Vector vEyePos;
};

extern Aimbot g_Aimbot;

