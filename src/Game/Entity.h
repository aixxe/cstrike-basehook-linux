#pragma once

class C_BaseEntity: public IClientEntity {
};

class C_BasePlayer: public C_BaseEntity {
	public:
		int GetFlags() {
			return *reinterpret_cast<int*>(uintptr_t(this) + NetVars::GetOffset("CBasePlayer", "m_fFlags"));
		}
};