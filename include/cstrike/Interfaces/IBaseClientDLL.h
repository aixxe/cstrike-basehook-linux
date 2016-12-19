#pragma once

class ClientClass;

enum ClientFrameStage_t: int {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

class IBaseClientDLL {
	public:
		ClientClass* GetAllClasses() {
			return GetVirtualFunction<ClientClass*(*)(IBaseClientDLL*)>(this, 8)(this);
		}

		void CreateMove(int sequence, float frametime, bool active) {
			return GetVirtualFunction<void(*)(IBaseClientDLL*, int, float, bool)>(this, 21)(this, sequence, frametime, active);
		}

		void FrameStageNotify(ClientFrameStage_t stage) {
			return GetVirtualFunction<void(*)(IBaseClientDLL*, ClientFrameStage_t)>(this, 35)(this, stage);
		}
};