#pragma once

enum ShouldTransmitState_t: int {
	SHOULDTRANSMIT_START = 0,
	SHOULDTRANSMIT_END
};

enum DataUpdateType_t: int {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED
};

class IClientNetworkable {
	public:
		virtual IClientUnknown*	GetIClientUnknown() = 0;
		virtual void Release() = 0;
		virtual ClientClass* GetClientClass() = 0;
		virtual void NotifyShouldTransmit(ShouldTransmitState_t state) = 0;
		virtual void OnPreDataChanged(DataUpdateType_t type) = 0;
		virtual void OnDataChanged(DataUpdateType_t type) = 0;
		virtual void PreDataUpdate(DataUpdateType_t type) = 0;
		virtual void PostDataUpdate(DataUpdateType_t type) = 0;
		virtual bool IsDormant(void) = 0;
		virtual int GetIndex(void) const = 0;
};