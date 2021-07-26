
#include "netvars.h"

enum classids
{
	Boomer = 0,
	Charger = 99,
	CTerrorPlayer = 232,
	Hunter = 263,
	Infected = 264,
	Jockey = 265,
	Smoker = 270,
	Spitter = 272,
	SurvivorBot = 275,
	Tank = 276,
	Witch = 277,
};

enum WeaponIDs
{
	WeaponCSBase = 0,
	AssaultRifle = 5,
	AutoShotgun = 4,
	BaseBackpackItem = 0,
	BoomerClaw = 41,
	Chainsaw = 20,
	ChargerClaw = 40,
	ColaBottles = 28,
	FireworkCrate = 29,
	FirstAidKit = 12,
	GasCan = 16,
	Gnome = 27,
	GrenadeLauncher = 21,
	HunterClaw = 39,
	Adrenaline = 23,
	ItemAmmoPack = 22,
	ItemDefibrillator = 24,
	ItemUpgradePackExplosive = 31,
	ItemUpgradePackIncendiary = 30,
	VomitJar = 25,
	JockeyClaw = 44,
	Molotov = 13,
	OxygenTank = 18,
	PainPills = 15,
	PipeBomb = 14,
	Pistol = 1,
	MagnumPistol = 32,
	PropaneTank = 17,
	PumpShotgun = 3,
	AK47 = 26,
	Desert = 9,
	M60 = 37,
	SG552 = 34,
	Chrome = 8,
	SPAS = 11,
	MP5 = 33,
	Silenced = 7,
	SmokerClaw = 42,
	SniperRifle = 6,
	AWP = 35,
	Military = 10,
	Scout = 36,
	SpitterClaw = 43,
	SubMachinegun = 2,
	TankClaw = 38,
	TerrorMeleeWeapon = 19,
	WeaponSpawn = 8,
};

enum TeamIndexes
{
	TEAM_UNASSIGNED,
	TEAM_SPECTATOR,
	TEAM_SURVIVOR,
	TEAM_ZOMBY,
	TEAM_IDK,
};

enum GROUP
{
	GROUP_INVALID = 0,
	GROUP_TANK,
	GROUP_BITCH,
	GROUP_SPECIAL,
	GROUP_INFECTED,
	GROUP_PLAYER
};

#define pRenderables 0x4
#define pNetworkables 0x8

struct CBaseEntity
{
	DWORD* GetModel()
	{
		PVOID pRenderable = (PVOID)(this + pRenderables);
		typedef DWORD* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pRenderable, 8)(pRenderable);
	}

	int GetIndex()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 8)(pNetworkable);
	}

	bool SetupBones(void* mtx)
	{
		PVOID pRenderable = (PVOID)(this + pRenderables);
		typedef bool(__thiscall* OriginalFn)(PVOID, void*, int, long, float);
		return getvfunc<OriginalFn>(pRenderable, 13)(pRenderable, mtx, 128, 0x100, 0);
	}

	bool IsDormant()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 7)(pNetworkable);
	}

	const Vector& GetAbsOrigin()
	{
		typedef const Vector& (__thiscall *GetAbsOrg_t)(PVOID);
		return getvfunc<GetAbsOrg_t>(this, 11)(this);
	}

	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (PVOID)(this + pNetworkables);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 1)(pNetworkable);
	}

	Vector GetMins()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_vecMins");
		return *(Vector*)((uintptr_t)this + iOffset);
	}
	Vector GetMaxs()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_vecMaxs");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	unsigned short GetSolidFlags()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_usSolidFlags");
		return *(unsigned short*)((uintptr_t)this + iOffset);
	}

	unsigned char GetLifeState()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_lifeState");
		return *(unsigned char*)((uintptr_t)this + iOffset);
	}

	int GetHealth()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_iHealth");
		return *(int*)((uintptr_t)this + iOffset);
	}

	Vector GetVelocity()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_vecVelocity[0]");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	Vector GetVecViewOffset()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_vecViewOffset[0]");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	Vector GetEyePosition()
	{
		return GetAbsOrigin() + GetVecViewOffset();
	}

	int GetFlags()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_fFlags");
		return *(int*)((uintptr_t)this + iOffset);
	}

	bool IsAlive()
	{
		return (GetLifeState() == LIFE_ALIVE && GetHealth() > 0);
	}

	int GetTeamNum()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_iTeamNum");
		return *(int*)((uintptr_t)this + iOffset);
	}

	Vector GetVecOrigin()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseEntity", "m_vecOrigin");
		return *(Vector*)((uintptr_t)this + iOffset);
	}

	Vector GetPunchAngle()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_vecPunchAngle");
		return *(Vector*)((DWORD)this + iOffset);
	}

	int GetTickBase()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BasePlayer", "m_nTickBase");
		return *(int*)((uintptr_t)this + iOffset);
	}

	HANDLE GetActiveWeaponHandle()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		return *(HANDLE*)((uintptr_t)this + iOffset);
	}

	inline const std::uint32_t Sequence()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseAnimating", "m_nSequence");
		return *(std::uint32_t*)(reinterpret_cast<std::uintptr_t>(this) + iOffset);
	}

	const GROUP GetGroup()
	{
		constexpr std::uint32_t m_Bitch = classids::Witch;
		constexpr std::uint32_t m_Tanks = classids::Tank;

		constexpr std::uint32_t m_Special[] = 
		{
	         classids::Boomer, classids::Charger, classids::Smoker,
	         classids::Hunter, classids::Jockey, classids::Spitter
		};

		constexpr std::uint32_t m_Infected = classids::Infected;
		constexpr std::uint32_t m_Player[] = { classids::CTerrorPlayer, classids::SurvivorBot };

		std::uint32_t m_ClassID = this->GetClientClass()->GetClassID;

		if (m_ClassID == m_Infected)
			return GROUP_INFECTED;

		if (m_ClassID == m_Bitch)
			return GROUP_BITCH;

		if (m_ClassID == m_Tanks)
			return GROUP_TANK;

		else if (std::find(std::begin(m_Special), std::end(m_Special), m_ClassID) != std::end(m_Special))
			return GROUP_SPECIAL;

		else if (std::find(std::begin(m_Player), std::end(m_Player), m_ClassID) != std::end(m_Player))
			return GROUP_PLAYER;

		return GROUP_INVALID;
	}

	const bool ValidEntity()
	{
		if (this->IsDormant())
			return false;

		const auto nTeam = this->GetTeamNum();

		if (nTeam != TEAM_SURVIVOR && nTeam != TEAM_ZOMBY)
			return false;

		auto m_Group = this->GetGroup();
		auto m_Sequence = this->Sequence();
		auto m_SolidFlags = this->GetSolidFlags();

		if (m_Group == GROUP_INVALID)
			return false;

		if (m_Group == GROUP_TANK)
		{
			if (m_SolidFlags & 4)
				return false;

			if (m_Sequence > 70)
				return false;
		}

		if (m_Group == GROUP_BITCH)
		{
			if (m_SolidFlags & 4)
				return false;

			if (m_Sequence > 70)
				return false;
		}

		else if (m_Group == GROUP_SPECIAL)
		{
			if (m_SolidFlags & 4)
				return false;
		}

		else if (m_Group == GROUP_INFECTED)
		{
			if (m_SolidFlags & 4)
				return false;

			if (m_Sequence > 305)
				return false;
		}

		return true;
	}
};

template<typename T>
inline T ReadPtr(const void *base, int o)
{
	return *(T *)((char *)base + o);
}

struct CBaseCombatWeapon
{
	float GetNextPrimaryAttack()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
		return *(float*)((uintptr_t)this + iOffset);
	}

	HANDLE Owner()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatWeapon", "m_hOwner");
		return *(HANDLE*)(reinterpret_cast<uintptr_t>(this) + iOffset);
	}

	inline float GetWeaponSpread()
	{
		return ReadPtr<float>(this, 3340);
	}

	int GetWeaponID()
	{
		typedef int(__thiscall* oWeaponID)(PVOID);
		return getvfunc< oWeaponID >(this, 383)(this);
	}

	bool HasAmmo()
	{
		static int iOffset = g_Netvarmanager.GetOffset("DT_BaseCombatWeapon", "m_iClip1");
		return ((*(PINT)((DWORD)this + iOffset)) > 0);
	}

	bool IsAimWep()
	{
		int iWpnID = GetWeaponID();

		return (iWpnID == AssaultRifle
			|| iWpnID == AutoShotgun
			|| iWpnID == Pistol
			|| iWpnID == MagnumPistol
			|| iWpnID == PumpShotgun
			|| iWpnID == AK47
			|| iWpnID == Desert
			|| iWpnID == M60
			|| iWpnID == SG552
			|| iWpnID == Chrome
			|| iWpnID == SPAS
			|| iWpnID == MP5
			|| iWpnID == Silenced
			|| iWpnID == SniperRifle
			|| iWpnID == AWP
			|| iWpnID == Scout
			|| iWpnID == Military);
	}
};

