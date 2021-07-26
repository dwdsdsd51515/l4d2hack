

class CDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, const Vector&, Vector&);
		return getvfunc<OriginalFn>(this, 12)(this, vIn, vOut);
	}
};