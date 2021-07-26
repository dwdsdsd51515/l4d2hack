

extern void InitialiseInterfaces();

extern IPlayerInfoManager* pInfoPlayer;
extern CGlobalVarsBase* pGlobalvars;
extern void* pClientMode;
extern CDebugOverlay* pDebugOverlay;
extern CEngineClient* pEngine;
extern IPanel* pPanel;
extern CEntityList* pEntList;
extern ISurface* pSurface;
extern IMaterialSystem* pMaterialSystem;
extern IVModelRender* pModelRender;
extern CModelInfo* pModel;
extern HLCLient* pClient;
extern CEnginetrace* pEngineTrace;

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
inline CreateInterfaceFn get_module_factory(HMODULE module)
{
	return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface"));
}