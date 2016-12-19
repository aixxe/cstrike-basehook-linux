#pragma once

inline void**& GetVirtualTable(void* baseclass) {
	return *reinterpret_cast<void***>(baseclass);
}

inline void* GetVirtualFunction(void* vftable, size_t index) {
	return reinterpret_cast<void*>(GetVirtualTable(vftable)[index]);
}

template <typename Fn> inline Fn GetVirtualFunction(void* vftable, size_t index) {
	return reinterpret_cast<Fn>(GetVirtualTable(vftable)[index]);
}