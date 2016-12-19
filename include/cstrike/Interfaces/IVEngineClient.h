#pragma once

class IVEngineClient {
	public:
		void GetScreenSize(int& width, int& height) {
			return GetVirtualFunction<void(*)(IVEngineClient*, int&, int&)>(this, 5)(this, width, height);
		}

		bool Con_IsVisible() {
			return GetVirtualFunction<bool(*)(IVEngineClient*)>(this, 11)(this);
		}

		int GetLocalPlayer() {
			return GetVirtualFunction<int(*)(IVEngineClient*)>(this, 12)(this);
		}

		float Time() {
			return GetVirtualFunction<float(*)(IVEngineClient*)>(this, 14)(this);
		}

		float GetLastTimeStamp() {
			return GetVirtualFunction<float(*)(IVEngineClient*)>(this, 15)(this);
		}
				
		void GetViewAngles(QAngle& angles) {
			return GetVirtualFunction<void(*)(IVEngineClient*, QAngle&)>(this, 19)(this, angles);
		}

		void SetViewAngles(QAngle& angles) {
			return GetVirtualFunction<void(*)(IVEngineClient*, QAngle&)>(this, 20)(this, angles);
		}

		int GetMaxClients() {
			return GetVirtualFunction<int(*)(IVEngineClient*)>(this, 21)(this);
		}

		bool IsInGame() {
			return GetVirtualFunction<bool(*)(IVEngineClient*)>(this, 26)(this);
		}

		bool IsConnected() {
			return GetVirtualFunction<bool(*)(IVEngineClient*)>(this, 27)(this);
		}

		const char* GetGameDirectory() {
			return GetVirtualFunction<const char*(*)(IVEngineClient*)>(this, 35)(this);
		}

		const char* GetLevelName() {
			return GetVirtualFunction<const char*(*)(IVEngineClient*)>(this, 51)(this);
		}

		void ClientCmd_Unrestricted(const char* command) {
			return GetVirtualFunction<void(*)(IVEngineClient*, const char*)>(this, 106)(this, command);
		}
};