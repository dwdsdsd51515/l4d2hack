

namespace ESP
{
	void DrawMonitor(int x, int y, CBaseEntity * entity);
	RECT DynamicBox(CBaseEntity* pPlayer, bool& PVS, CBaseEntity* local);
	void draw(CBaseEntity* local);
	void DrawPlayer(CBaseEntity * pEntity,CBaseEntity * local);
	void DrawBox(const RECT& rect);
	void drawradar(int screenwidght, int screenheight, CBaseEntity* local);
	void DrawRadarBack(int screenwidght, int screenheight);
	void DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, Vector vAngle);
	void drawvelocity(int screenWidth, int screenHeight, CBaseEntity* local_player);
}

