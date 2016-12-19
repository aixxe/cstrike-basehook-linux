#pragma once

typedef unsigned short ModelInstanceHandle_t;

class model_t;
class studiohdr_t;
class studiohwdata_t;
class IClientRenderable;
class matrix3x4_t;
class StudioDecalHandle_t;
class IMaterial;

struct DrawModelState_t {
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	IClientRenderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	StudioDecalHandle_t* m_decals;
	int m_drawFlags;
	int m_lod;
};

struct ModelRenderInfo_t {
	Vector origin;
	QAngle angles;
	IClientRenderable* pRenderable;
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
};

enum OverrideType_t: int {
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IVModelRender {
	public:
		void ForcedMaterialOverride(IMaterial* material, OverrideType_t override_type = OVERRIDE_NORMAL) {
			GetVirtualFunction<void(*)(IVModelRender*, IMaterial*, OverrideType_t)>(this, 1)(this, material, override_type);
		}

		void DrawModelExecute(DrawModelState_t const& state, ModelRenderInfo_t const& info, matrix3x4_t* bone) {
			GetVirtualFunction<void(*)(IVModelRender*, DrawModelState_t const&, ModelRenderInfo_t const&, matrix3x4_t*)>(this, 19)(this, state, info, bone);
		}
};