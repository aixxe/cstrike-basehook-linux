#pragma once

#define MAXSTUDIOBONES 128

#define BONE_USED_MASK 0x7FF00
#define BONE_USED_BY_ANYTHING 0x7FF00
#define BONE_USED_BY_HITBOX 0x100
#define BONE_USED_BY_ATTACHMENT 0x200
#define BONE_USED_BY_VERTEX_MASK 0x3FC00
#define BONE_USED_BY_VERTEX_LOD0 0x400
#define BONE_USED_BY_VERTEX_LOD1 0x800	
#define BONE_USED_BY_VERTEX_LOD2 0x1000  
#define BONE_USED_BY_VERTEX_LOD3 0x2000
#define BONE_USED_BY_VERTEX_LOD4 0x4000
#define BONE_USED_BY_VERTEX_LOD5 0x8000
#define BONE_USED_BY_VERTEX_LOD6 0x10000
#define BONE_USED_BY_VERTEX_LOD7 0x20000
#define BONE_USED_BY_BONE_MERGE	0x40000

struct mstudiobbox_t {
	public:
		inline const char* GetName() {
			if (szhitboxnameindex == 0)
				return nullptr;

			return ((const char*)this) + szhitboxnameindex;
		}

		int bone;
		int group;
		Vector bbmin;
		Vector bbmax;
		int szhitboxnameindex;
		int unused[8];
};

struct mstudiohitboxset_t {
	public:
		inline const char* GetName() {
			return ((const char*)this) + sznameindex;
		}

		inline mstudiobbox_t* GetHitbox(int i) const {
			return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i;
		};

		int sznameindex;
		int	numhitboxes;
		int	hitboxindex;
};

class studiohdr_t {
	public:
		inline const mstudiohitboxset_t* GetHitboxSet(int i) {
			if (i > numhitboxsets)
				return nullptr;

			return (const mstudiohitboxset_t*)((unsigned char*)this + hitboxsetindex) + i;
		}

		int id;
		int version;
		long checksum;
		char szName[64];
		int length;
		Vector vecEyePos;
		Vector vecIllumPos;
		Vector vecHullMin;
		Vector vecHullMax;
		Vector vecBBMin;
		Vector vecBBMax;
		int flags;
		int numBones;
		int indexBones;
		int numbonecontrollers;
		int bonecontrollerindex;
		int numhitboxsets;
		int hitboxsetindex;
		int numlocalanim;
		int localanimindex;
		int numlocalseq;
		int localseqindex;
		int activitylistversion;
		int eventsindexed;
		int numtextures;
		int textureindex;
};

class model_t;

class IVModelInfoClient {
	public:
		const char* GetModelName(const model_t* model) {
			return GetVirtualFunction<const char*(*)(IVModelInfoClient*, const model_t*)>(this, 4)(this, model);
		}

		studiohdr_t* GetStudioModel(const model_t* model) {
			return GetVirtualFunction<studiohdr_t*(*)(IVModelInfoClient*, const model_t*)>(this, 29)(this, model);
		}
};