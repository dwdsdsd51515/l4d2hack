#include "hooks.h"
#include "sigs.h"


void InitialiseInterfaces()
{
	auto EnginePointer = get_module_factory(GetModuleHandleW(L"engine.dll"));
	auto ClientPointer = get_module_factory(GetModuleHandleW(L"client.dll"));
	auto VGUISurfacePointer = get_module_factory(GetModuleHandleW(L"vguimatsurface.dll"));
	auto VGUI2Pointer = get_module_factory(GetModuleHandleW(L"vgui2.dll"));
	auto MaterialPointer = get_module_factory(GetModuleHandleW(L"materialsystem.dll"));
	auto ServerPointer = get_module_factory(GetModuleHandleW(L"server.dll"));

	pInfoPlayer = (IPlayerInfoManager*)ServerPointer("PlayerInfoManager002", nullptr);
	pClient = (HLCLient*)ClientPointer("VClient016", nullptr);
	pEngine = (CEngineClient*)EnginePointer("VEngineClient013", nullptr);
	pEntList = (CEntityList*)ClientPointer("VClientEntityList003", nullptr);
	pModel = (CModelInfo*)EnginePointer("VModelInfoClient004", nullptr);
	pModelRender = (IVModelRender*)EnginePointer("VEngineModel016", nullptr);
	pMaterialSystem = (IMaterialSystem*)MaterialPointer("VMaterialSystem080", nullptr);
	pPanel = (IPanel*)VGUI2Pointer("VGUI_Panel009", nullptr);
	pSurface = (ISurface*)VGUISurfacePointer("VGUI_Surface031", nullptr);
	pEngineTrace = (CEnginetrace*)EnginePointer("EngineTraceClient003", nullptr);
	pDebugOverlay = (CDebugOverlay*)EnginePointer("VDebugOverlay003", nullptr);

	pClientMode = **(void***)(Findrekt("client.dll", "89 04 B5 ? ? ? ? E8") + 3);
	pGlobalvars = pInfoPlayer->GetGlobalVars();
}

IPlayerInfoManager* pInfoPlayer;
CGlobalVarsBase* pGlobalvars;
void* pClientMode;
CDebugOverlay* pDebugOverlay;
CEngineClient* pEngine;
IPanel* pPanel;
CEntityList* pEntList;
ISurface* pSurface;
IMaterialSystem* pMaterialSystem;
IVModelRender* pModelRender;
CModelInfo* pModel;
HLCLient* pClient;
CEnginetrace* pEngineTrace;

