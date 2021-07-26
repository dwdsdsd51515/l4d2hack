

template <typename t>
t getvfunc(void* class_pointer, size_t index)
{
	return (*(t**)class_pointer)[index];
}

#define	LIFE_ALIVE	0 
#define	FL_ONGROUND		(1<<0)
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_USE			(1 << 5)

#include "modelsinfo.h"
#include "debugoverlay.h"
#include "md5hash.h"
#include "recvprop.h"
#include "baseentity.h"
#include "engineclient.h"
#include "surface.h"
#include "materials.h"
#include "globalvars.h"
#include "panels.h"
#include "usercmd.h"
#include "enginetrace.h"