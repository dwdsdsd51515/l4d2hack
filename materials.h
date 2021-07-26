#pragma once


struct ModelRenderInfo_t
{
	Vector origin;
	Vector angles;
	void* renderable;
	const void *pModel;
	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const Vector* lightingOrigin;
	int flags;
	int entity_index;
};

enum MaterialVarFlag
{
	NO_DRAW = (1 << 2),
	ZNEARER = (1 << 10),
	NOCULL = (1 << 13),
	NOFOG = (1 << 14),
	IGNOREZ = (1 << 15),
	HALFLAMBERT = (1 << 27)
};

class IMaterial
{
public:
	void ColorModulate(float r, float g, float b)
	{
		typedef void(__thiscall* ColorModulateFn)(void*, float, float, float);
		getvfunc<ColorModulateFn>(this, 28)(this, r, g, b);
	}

	void SetMaterialVarFlag(MaterialVarFlag flag, bool on)
	{
		typedef void(__thiscall* SetMaterialVarFlagFn)(void*, MaterialVarFlag, bool);
		getvfunc<SetMaterialVarFlagFn>(this, 29)(this, flag, on);
	}
};

class IMaterialSystem
{
public:
	IMaterial *FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL)
	{
		typedef IMaterial*(__thiscall* OriginalFn)(PVOID, char const*, const char*, bool, const char*);
		return getvfunc<OriginalFn>(this, 71)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
};

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* mat)
	{
		typedef void(__thiscall *OriginalFn)(void*, IMaterial*, int);
		return getvfunc<OriginalFn>(this, 1)(this, mat, 0);
	}
};
