


class IPanel
{
public:
	void SetMouseInputEnabled(unsigned int iPanel, bool bState)
	{
		return (getvfunc<void(__thiscall*)(PVOID, int, bool)>(this, 32))(this, iPanel, bState);
	}

	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return getvfunc<OriginalFn>(this, 36)(this, vguiPanel);
	}
};