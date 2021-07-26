#pragma once

enum
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD = 1,
	HITGROUP_CHEST = 2,
	HITGROUP_STOMACH = 3,
	HITGROUP_LEFTARM = 4,
	HITGROUP_RIGHTARM = 5,
	HITGROUP_LEFTLEG = 6,
	HITGROUP_RIGHTLEG = 7,
	HITGROUP_GEAR = 10,
};

struct mstudiobbox
{
	int         bone;
	int         group;
	Vector		bbmin;
	Vector		bbmax;
	int         szhitboxnameindex;
	int         unused[8];
};

struct mstudiohitboxset
{
	int                   sznameindex;
	inline char* const    pszName(void) const { return ((char*)this) + sznameindex; }
	int                   numhitboxes;
	int                   hitboxindex;
	inline mstudiobbox*   pHitbox(int i) const { return (mstudiobbox*)(((BYTE*)this) + hitboxindex) + i; };
};

struct studiohdr
{
	unsigned char     pad[0xAC];
	int               numhitboxsets;
	int               hitboxsetindex;

	mstudiohitboxset* pHitboxSet(int i) const
	{
		return (mstudiohitboxset*)(((BYTE*)this) + hitboxsetindex) + i;
	};

	inline int GetHitboxCount(int set) const
	{
		mstudiohitboxset const* s = pHitboxSet(set);
		if (!s)
			return 0;
		return s->numhitboxes;
	}
};

class CModelInfo
{
public:
	inline const char* GetModelName(const void* Model)
	{
		return getvfunc<const char*(__thiscall *)(void*, const void*)>(this, 3)(this, Model);
	}
	studiohdr* GetStudiomodel(const DWORD *mod)
	{
		typedef studiohdr* (__thiscall* GetStudiomodelFn)(void*, const DWORD*);
		return getvfunc< GetStudiomodelFn >(this, 30)(this, mod);
	}
};