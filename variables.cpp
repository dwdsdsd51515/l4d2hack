#include "variables.h"

void CConfig::Setup()
{
	SetupValue(gCvars.flRadarPos_x, false, ("Config"), ("flRadarPos_x"));
	SetupValue(gCvars.flRadarPos_y, false, ("Config"), ("flRadarPos_y"));
	SetupValue(gCvars.SMOOTHYAW, false, ("Config"), ("SMOOTHYAW"));
	SetupValue(gCvars.SMOOTHPITCH, false, ("Config"), ("SMOOTHPITCH"));
	SetupValue(gCvars.ENABLEAIM, false, ("Config"), ("ENABLEAIM"));
	SetupValue(gCvars.AIMONFIRE, false, ("Config"), ("AIMONFIRE"));
	SetupValue(gCvars.AIMFOV, false, ("Config"), ("AIMFOV"));
	SetupValue(gCvars.NORECOIL, false, ("Config"), ("NORECOIL"));
	SetupValue(gCvars.NOSPREAD, false, ("Config"), ("NOSPREAD"));
	SetupValue(gCvars.AUTOFIRE, false, ("Config"), ("AUTOFIRE"));
	SetupValue(gCvars.SILENTAIM, false, ("Config"), ("SILENTAIM"));
	SetupValue(gCvars.ESPBOX, false, ("Config"), ("ESPBOX"));
	SetupValue(gCvars.ESPNAME, false, ("Config"), ("ESPNAME"));
	SetupValue(gCvars.ESPHEALTH, false, ("Config"), ("ESPHEALTH"));
	SetupValue(gCvars.CHAMS, false, ("Config"), ("CHAMS"));
	SetupValue(gCvars.CHAMSXQZ, false, ("Config"), ("CHAMSXQZ"));
	SetupValue(gCvars.CHAMHAND, false, ("Config"), ("CHAMHAND"));
	SetupValue(gCvars.AUTOBH, false, ("Config"), ("AUTOBH"));
	SetupValue(gCvars.AUTOFIRE, false, ("Config"), ("AUTOFIRE"));
	SetupValue(gCvars.SILENTAIM, false, ("Config"), ("SILENTAIM"));
	SetupValue(gCvars.radar, false, ("Config"), ("radar"));
	SetupValue(gCvars.watermark, false, ("Config"), ("watermark"));
	SetupValue(gCvars.velocity, false, ("Config"), ("velocity"));
	SetupValue(gCvars.SILENTAIM, false, ("Config"), ("SILENTAIM"));
	SetupValue(gCvars.triggerkey, false, ("Config"), ("triggerkey"));
	SetupValue(gCvars.trigenable, false, ("Config"), ("trigenable"));
	SetupValue(gCvars.trighead, false, ("Config"), ("trighead"));
	SetupValue(gCvars.triggerbody, false, ("Config"), ("triggerbody"));
	SetupValue(gCvars.trigerdelay, false, ("Config"), ("trigerdelay"));
	SetupValue(gCvars.TRIGLIMB, false, ("Config"), ("TRIGLIMB"));
	SetupValue(gCvars.NOVOMIT, false, ("Config"), ("NOVOMIT"));
	SetupValue(gCvars.espcolor[0], false, ("Config"), ("espcolor0"));
	SetupValue(gCvars.espcolor[1], false, ("Config"), ("espcolor1"));
	SetupValue(gCvars.espcolor[2], false, ("Config"), ("espcolor2"));
	SetupValue(gCvars.SPEEDKEY, false, ("Config"), ("SPEEDKEY"));
	SetupValue(gCvars.SPEEDFAST, false, ("Config"), ("SPEEDFAST"));
	SetupValue(gCvars.LAGKEY, false, ("Config"), ("LAGKEY"));
	SetupValue(gCvars.LAGFAST, false, ("Config"), ("LAGFAST"));
	SetupValue(gCvars.drawmonitor, false, ("Config"), ("drawmonitor"));
	SetupValue(gCvars.f1monitorpos_x, false, ("Config"), ("f1monitorpos_x"));
	SetupValue(gCvars.f1monitorpos_y, false, ("Config"), ("f1monitorpos_y"));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\l4d2hack\\");
		file = std::string(path) + ("\\l4d2hack\\config.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\l4d2hack\\");
		file = std::string(path) + ("\\l4d2hack\\config.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}
}

CConfig* Config = new CConfig();
CGlobalVariables gCvars;