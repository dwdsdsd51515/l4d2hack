

struct raytrace
{
	raytrace(const Vector& src, const Vector& dest) : start(src), delta(dest - src) { isSwept = delta.x || delta.y || delta.z; }
	Vector start{ };
	float pad{ };
	Vector delta{ };
	byte pad2[40]{ };
	bool isRay{ true };
	bool isSwept{ };
};


struct tracefitlers
{
	tracefitlers(const CBaseEntity* entity) : skip{ entity } { }
	virtual bool shouldHitEntity(CBaseEntity* entity, int) { return entity != skip; }
	virtual int getTraceType() const { return 0; }
	const void* skip;
};

struct traceclass
{
	Vector		startpos;
	Vector		endpos;

	struct
	{
		Vector	normal;
		float	distance;
		char	type;
		char	signbits;
		short	unused;
	}
	plane;

	float		fraction;
	int			contents;
	short		dispflags;
	bool		allsolid;
	bool		startsolid;
	float		fractionleftsolid;
	const char	*name;
	short		surfaceprops;
	short		flags;
	int			hitgroup;
	short		physicsbone;
	CBaseEntity	*pent;
	int			hitbox;
};

class CEnginetrace
{
public:
	void TraceRay(const raytrace &ray, tracefitlers *pTraceFilter, traceclass *ptrace)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const raytrace &, int, tracefitlers *, traceclass *);
		return getvfunc<OriginalFn>(this, 5)(this, ray, 0x46004003, pTraceFilter, ptrace);
	}
};

