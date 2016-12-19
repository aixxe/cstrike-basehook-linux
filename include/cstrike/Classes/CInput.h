#pragma once

class CUserCmd;

class CInput {
	public:
		CUserCmd* GetUserCmd(int index) {
			return GetVirtualFunction<CUserCmd*(*)(CInput*, int)>(this, 8)(this, index);
		}
};