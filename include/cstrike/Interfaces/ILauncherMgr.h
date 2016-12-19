#pragma once

class CShowPixelsParams;

typedef void* PseudoGLContextPtr;

class ILauncherMgr {
	public:
		void PumpWindowsMessageLoop() {
			return GetVirtualFunction<void(*)(ILauncherMgr*)>(this, 15)(this);
		}

		PseudoGLContextPtr GetMainContext() {
			return GetVirtualFunction<PseudoGLContextPtr(*)(ILauncherMgr*)>(this, 22)(this);
		}

		PseudoGLContextPtr CreateExtraContext() {
			return GetVirtualFunction<PseudoGLContextPtr(*)(ILauncherMgr*)>(this, 24)(this);
		}

		void DeleteContext(PseudoGLContextPtr context) {
			return GetVirtualFunction<void(*)(ILauncherMgr*, PseudoGLContextPtr)>(this, 27)(this, context);
		}

		bool MakeContextCurrent(PseudoGLContextPtr context) {
			return GetVirtualFunction<bool(*)(ILauncherMgr*, PseudoGLContextPtr)>(this, 26)(this, context);
		}

		void PumpWindowsMessageLoop(CShowPixelsParams* params) {
			return GetVirtualFunction<void(*)(ILauncherMgr*, CShowPixelsParams*)>(this, 29)(this, params);
		}

		void* GetWindowRef() {
			return GetVirtualFunction<void*(*)(ILauncherMgr*)>(this, 32)(this);
		}
};