#pragma once

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

		inline CRC32_t GetChecksum() {
			CRC32_t crc;

			CRC32_Init(&crc);

			CRC32_ProcessBuffer(&crc, &this->command_number, sizeof(this->command_number));
			CRC32_ProcessBuffer(&crc, &this->tick_count, sizeof(this->tick_count));
			CRC32_ProcessBuffer(&crc, &this->viewangles, sizeof(this->viewangles));
			CRC32_ProcessBuffer(&crc, &this->forwardmove, sizeof(this->forwardmove));
			CRC32_ProcessBuffer(&crc, &this->sidemove, sizeof(this->sidemove));
			CRC32_ProcessBuffer(&crc, &this->upmove, sizeof(this->upmove));
			CRC32_ProcessBuffer(&crc, &this->buttons, sizeof(this->buttons));
			CRC32_ProcessBuffer(&crc, &this->impulse, sizeof(this->impulse));
			CRC32_ProcessBuffer(&crc, &this->weaponselect, sizeof(this->weaponselect));
			CRC32_ProcessBuffer(&crc, &this->weaponsubtype, sizeof(this->weaponsubtype));
			CRC32_ProcessBuffer(&crc, &this->random_seed, sizeof(this->random_seed));
			CRC32_ProcessBuffer(&crc, &this->mousedx, sizeof(this->mousedx));
			CRC32_ProcessBuffer(&crc, &this->mousedy, sizeof(this->mousedy));

			CRC32_Final(&crc);

			return crc;
		}
};

class CVerifiedUserCmd {
	public:
		CUserCmd m_cmd;
		CRC32_t m_crc;
};