#pragma once

#include <iostream>
#include <dlfcn.h>

typedef void* (*InstantiateInterfaceFn) ();

class InterfaceReg {
	public:
		InstantiateInterfaceFn m_CreateFn;
		const char* m_pName;
		InterfaceReg* m_pNext;
};

inline const InterfaceReg* GetInterfaces(const char* library) {
	// Open a handle to the library.
	void* library_handle = dlopen(library, RTLD_NOLOAD | RTLD_NOW);

	// Check for an exported 's_pInterfaceRegs' symbol. (easy mode)
	void* interfaceregs_symbol = dlsym(library_handle, "s_pInterfaceRegs");

	if (interfaceregs_symbol) {
		// Close the handle to the library.
		dlclose(library_handle);

		// Return interface list.
		return *reinterpret_cast<InterfaceReg**>(interfaceregs_symbol);
	}

	// Get the address to the exported 'CreateInterface' symbol.
	void* createinterface_symbol = dlsym(library_handle, "CreateInterface");

	// Close the handle to the library.
	dlclose(library_handle);

	// Get the jump displacement to the 'CreateInterfaceInternal' function.
	uintptr_t jump_instruction = uintptr_t(createinterface_symbol) + 4;
	int32_t jump_displacement = *reinterpret_cast<int32_t*>(jump_instruction + 1);

	// Calculate the absolute jump address relative to the next instruction.
	uintptr_t createinterfaceinternal_addr = (jump_instruction + 5) + jump_displacement;

	// Read the address to the 'InterfaceReg::s_pInterfaceRegs' linked list from 11 bytes in.
	uintptr_t interface_list = *reinterpret_cast<uintptr_t*>(createinterfaceinternal_addr + 11);

	return *reinterpret_cast<InterfaceReg**>(interface_list);
}

template <typename T = void*> inline T* GetInterface(const char* library, const char* partial_version) {
	for (const InterfaceReg* current = GetInterfaces(library); current; current = current->m_pNext) {
		if (std::string(current->m_pName).find(partial_version) != std::string::npos) {
			return reinterpret_cast<T*>(current->m_CreateFn());
		}
	}

	return nullptr;
}