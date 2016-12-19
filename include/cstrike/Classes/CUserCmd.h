#pragma once

typedef unsigned long CRC32_t;

class CUserCmd {
	virtual ~CUserCmd() {};

	public:
		int command_number;
		int tick_count;
		QAngle viewangles;
		float forwardmove;
		float sidemove;
		float upmove;
		int buttons;
		unsigned char impulse;
		int weaponselect;
		int weaponsubtype;
		int random_seed;
		short mousedx;
		short mousedy;
		bool hasbeenpredicted;
};

class CVerifiedUserCmd {
	public:
		CUserCmd m_cmd;
		CRC32_t m_crc;
};