
void OverridematerialXQZ(IMaterial* mat, float r, float g, float b)
{
	mat->SetMaterialVarFlag(IGNOREZ, true);
	mat->SetMaterialVarFlag(ZNEARER, true);
	mat->SetMaterialVarFlag(NOCULL, true);
	mat->SetMaterialVarFlag(NOFOG, true);
	mat->SetMaterialVarFlag(HALFLAMBERT, true);
	mat->ColorModulate(r / 255, g / 255, b / 255);
	pModelRender->ForcedMaterialOverride(mat);
}

void Overridematerial(IMaterial* mat, float r, float g, float b)
{
	mat->SetMaterialVarFlag(IGNOREZ, false);
	mat->SetMaterialVarFlag(ZNEARER, true);
	mat->SetMaterialVarFlag(NOCULL, true);
	mat->SetMaterialVarFlag(NOFOG, true);
	mat->SetMaterialVarFlag(HALFLAMBERT, true);
	mat->ColorModulate(r / 255, g / 255, b / 255);
	pModelRender->ForcedMaterialOverride(mat);
}

typedef void(__thiscall *DrawModelExecuteFn)(IVModelRender*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
DrawModelExecuteFn draw_model_original = nullptr;

void __stdcall hkDrawModelExecute(void* state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	static IMaterial* material = pMaterialSystem->FindMaterial("debug/debugambientcube", "Model textures");
	static IMaterial* vomitboomer = pMaterialSystem->FindMaterial(("particle/screenspaceboomervomit"), "Particle textures");

	if (pInfo.pModel && pInfo.entity_index && material && vomitboomer)
	{
		const char *pszModelName = pModel->GetModelName(pInfo.pModel);
		CBaseEntity* pEntity = (CBaseEntity*)pEntList->GetClientEntity(pInfo.entity_index);

		vomitboomer->SetMaterialVarFlag(NO_DRAW, gCvars.NOVOMIT);

		if (gCvars.CHAMHAND && pszModelName && strstr(pszModelName, "models/weapons/arms/v_arms"))
		{
			Overridematerial(material, gCvars.espcolor[0], gCvars.espcolor[1], gCvars.espcolor[2]);
		}

		if (gCvars.CHAMS && pEntity)
		{
			if (pEntity->GetTeamNum() == TEAM_ZOMBY && pEntity->GetGroup() && pEntity->ValidEntity())
			{
				if (gCvars.CHAMSXQZ)
				{
					OverridematerialXQZ(material, gCvars.espcolor[1], gCvars.espcolor[2], gCvars.espcolor[0]);
					draw_model_original(pModelRender, state, pInfo, pCustomBoneToWorld);
				}
				Overridematerial(material, gCvars.espcolor[0], gCvars.espcolor[1], gCvars.espcolor[2]);
			}
		}
	}

	draw_model_original(pModelRender, state, pInfo, pCustomBoneToWorld);
	pModelRender->ForcedMaterialOverride(nullptr);
}