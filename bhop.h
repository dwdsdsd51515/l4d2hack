#pragma once


void RunBhop(CUserCmd* cmd, CBaseEntity* pLocal)
{
	static bool jumped_last_tick = false;
	static bool should_fake_jump = false;

	if (!jumped_last_tick && should_fake_jump)
	{
		should_fake_jump = false;
		cmd->buttons |= IN_JUMP;
	}
	else if (cmd->buttons & IN_JUMP)
	{
		if (pLocal->GetFlags() & FL_ONGROUND)
		{
			jumped_last_tick = true;
			should_fake_jump = true;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
			jumped_last_tick = false;
		}
	}
	else
	{
		jumped_last_tick = false;
		should_fake_jump = false;
	}
}