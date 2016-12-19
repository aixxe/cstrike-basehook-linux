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

class model_t;

class IVModelInfoClient {
	public:
		const char* GetModelName(const model_t* model) {
			return GetVirtualFunction<const char*(*)(IVModelInfoClient*, const model_t*)>(this, 4)(this, model);
		}
};