#pragma once

class model_t;

class IVModelInfoClient {
	public:
		const char* GetModelName(const model_t* model) {
			return GetVirtualFunction<const char*(*)(IVModelInfoClient*, const model_t*)>(this, 4)(this, model);
		}
};