#pragma once

#define TEXTURE_GROUP_LIGHTMAP "Lightmaps"
#define TEXTURE_GROUP_WORLD "World textures"
#define TEXTURE_GROUP_MODEL "Model textures"
#define TEXTURE_GROUP_VGUI "VGUI textures"
#define TEXTURE_GROUP_PARTICLE "Particle textures"
#define TEXTURE_GROUP_DECAL "Decal textures"
#define TEXTURE_GROUP_SKYBOX "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS "ClientEffect textures"
#define TEXTURE_GROUP_OTHER "Other textures"
#define TEXTURE_GROUP_PRECACHED "Precached"
#define TEXTURE_GROUP_CUBE_MAP "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET "RenderTargets"
#define TEXTURE_GROUP_RUNTIME_COMPOSITE "Runtime Composite"
#define TEXTURE_GROUP_UNACCOUNTED "Unaccounted textures"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER  "Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP "Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR "Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD "World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS "Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER "Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS "Morph Targets"

enum MaterialVarFlags_t {
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30)
};

typedef unsigned short MaterialHandle_t;

class KeyValues;

class IMaterial {
	public:
		const char* GetName() {
			return GetVirtualFunction<const char*(*)(IMaterial*)>(this, 0)(this);
		}

		const char* GetTextureGroupName() {
			return GetVirtualFunction<const char*(*)(IMaterial*)>(this, 1)(this);
		}

		void IncrementReferenceCount() {
			return GetVirtualFunction<void(*)(IMaterial*)>(this, 12)(this);
		}

		void DecrementReferenceCount() {
			return GetVirtualFunction<void(*)(IMaterial*)>(this, 13)(this);
		}

		void AlphaModulate(float alpha) {
			return GetVirtualFunction<void(*)(IMaterial*, float)>(this, 27)(this, alpha);
		}

		void ColorModulate(float red, float green, float blue) {
			return GetVirtualFunction<void(*)(IMaterial*, float, float, float)>(this, 28)(this, red, green, blue);
		}

		void SetMaterialVarFlag(MaterialVarFlags_t flags, bool state) {
			return GetVirtualFunction<void(*)(IMaterial*, MaterialVarFlags_t, bool)>(this, 29)(this, flags, state);
		}

		bool GetMaterialVarFlag(MaterialVarFlags_t flags) {
			return GetVirtualFunction<bool(*)(IMaterial*, MaterialVarFlags_t)>(this, 30)(this, flags);
		}

		bool IsErrorMaterial() {
			return GetVirtualFunction<bool(*)(IMaterial*)>(this, 42)(this);
		}
};

class IMaterialSystem {
	public:
		IMaterial* CreateMaterial(const char* name, KeyValues* keyvalues) {
			return GetVirtualFunction<IMaterial*(*)(IMaterialSystem*, const char*, KeyValues*)>(this, 70)(this, name, keyvalues);
		}

		IMaterial* FindMaterial(char const* name, const char* group, bool complain = true, const char* complain_prefix = NULL) {
			return GetVirtualFunction<IMaterial*(*)(IMaterialSystem*, const char*, const char*, bool, const char*)>(this, 71)(this, name, group, complain, complain_prefix);
		}

		bool IsMaterialLoaded(char const* name) {
			return GetVirtualFunction<bool(*)(IMaterialSystem*, const char*)>(this, 72)(this, name);
		}

		MaterialHandle_t FirstMaterial() {
			return GetVirtualFunction<MaterialHandle_t(*)(IMaterialSystem*)>(this, 73)(this);
		}

		MaterialHandle_t NextMaterial(MaterialHandle_t material) {
			return GetVirtualFunction<MaterialHandle_t(*)(IMaterialSystem*, MaterialHandle_t)>(this, 74)(this, material);
		}

		MaterialHandle_t InvalidMaterial() {
			return GetVirtualFunction<MaterialHandle_t(*)(IMaterialSystem*)>(this, 75)(this);
		}

		IMaterial* GetMaterial(MaterialHandle_t material) {
			return GetVirtualFunction<IMaterial*(*)(IMaterialSystem*, MaterialHandle_t)>(this, 76)(this, material);
		}
};