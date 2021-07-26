


class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	std::int32_t command_number;
	std::int32_t tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	std::int32_t buttons;
};


