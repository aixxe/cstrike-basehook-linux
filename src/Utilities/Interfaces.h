#pragma once

typedef void* (*InstantiateInterfaceFn) ();

class InterfaceReg {
	public:
		InstantiateInterfaceFn m_CreateFn;
		const char* m_pName;
		InterfaceReg* m_pNext;
};

inline const InterfaceReg* GetInterfaces(const char* library) {
	// Find the pointer to the 'InterfaceReg::s_pInterfaceRegs' linked list - same on all game libraries.
	uintptr_t interface_list_addr = FindPattern(library, "\x89\x10\x8B\x15\x00\x00\x00\x00\xA3", "xxxx????x");
	
	if (interface_list_addr)
		return **reinterpret_cast<InterfaceReg***>(interface_list_addr + 4);

	return nullptr;
}

template <typename T> inline T* GetInterface(const char* library, const char* partial_version) {
	for (const InterfaceReg* current = GetInterfaces(library); current; current = current->m_pNext) {
		if (std::string(current->m_pName).find(partial_version) != std::string::npos) {
			return reinterpret_cast<T*>(current->m_CreateFn());
		}
	}

	return nullptr;
}