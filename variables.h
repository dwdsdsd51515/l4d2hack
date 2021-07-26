#pragma once

#include <vector>
#include <ShlObj.h>
#include <sstream>

template <typename T>
class ConfigValue
{
public:
	ConfigValue(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
protected:
	std::vector<ConfigValue<float>*> floats;
private:
	void SetupValue(float&, float, std::string, std::string);
public:
	CConfig()
	{
		Setup();
	}

	void Setup();
	void Save();
	void Load();
};

class CGlobalVariables
{
public:
	float SMOOTHYAW;
	float SMOOTHPITCH;
	float ENABLEAIM;
	float AIMONFIRE;
	float AIMFOV;
	float NORECOIL;
	float NOSPREAD;
	float AUTOFIRE;
	float SILENTAIM;
	float ESPBOX;
	float ESPNAME;
	float ESPHEALTH;
	float CHAMS;
	float CHAMSXQZ;
	float CHAMHAND;
	float AUTOBH;
	float iSavedRadarX;
	float iSavedRadarY;
	float flRadarPos_x = 120;
	float flRadarPos_y = 120;
	float radar;
	float espcolor[3];
	float watermark;
	float velocity;
	float triggerkey;
	float trigenable;
	float trighead;
	float triggerbody;
	float trigerdelay;
	float TRIGLIMB;
	float NOVOMIT;
	float SPEEDKEY;
	float SPEEDFAST;
	float LAGKEY;
	float LAGFAST;
	float drawmonitor;
	float f1monitorpos_x = 400;
	float f1monitorpos_y = 400;
};

extern CConfig* Config;
extern CGlobalVariables gCvars;
