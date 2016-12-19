#pragma once

class model_t;

class IClientRenderable {
	public:
		virtual IClientUnknown*	GetIClientUnknown() = 0;
		virtual Vector const& GetRenderOrigin(void) = 0;
		virtual QAngle const& GetRenderAngles(void) = 0;

		const model_t* GetModel() {
			return GetVirtualFunction<const model_t*(*)(void*)>(this, 9)(this);
		}

		bool SetupBones(matrix3x4_t* bonematrix, int maxbones, int mask, float curtime = 0) {
			return GetVirtualFunction<bool(*)(IClientRenderable*, matrix3x4_t*, int, int, float)>(this, 16)(this, bonematrix, maxbones, mask, curtime);
		}
};