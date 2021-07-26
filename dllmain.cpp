

#include "hooks.h"
#include "model.h"
#include "panel.h"
#include "cmove.h"
#include "hooking.hpp"

vmt_hook* paint;
vmt_hook* engine;
vmt_hook* drawmodel;

void InitThread()
{	
	static bool once = false;

	if (!once)
	{
		InitialiseInterfaces();
		g_Netvarmanager.Init();

		paint = new vmt_hook(pPanel);
		painttraverse_original = paint->hook<paint_traverse_t>(41, hkPaintTraverse);

		engine = new vmt_hook(pEngine);
		org_SetViewAngles = engine->hook<SetViewAngleFn>(20, hooked_SetViewAngles);

		drawmodel = new vmt_hook(pModelRender);
		draw_model_original = drawmodel->hook<DrawModelExecuteFn>(19, hkDrawModelExecute);

		Draw::InitFonts();

		once = true;
	}
}

int __stdcall DllMain(void*, int r, void*)
{
	if (r == 1)
	{
		InitThread();
	}

	return 1;
}
