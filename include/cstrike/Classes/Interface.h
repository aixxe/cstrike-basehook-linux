#pragma once

typedef void* (*CreateInterfaceFn) (const char*, int*);
typedef void* (*InstantiateInterfaceFn) ();

class InterfaceReg {
	public:
		InstantiateInterfaceFn m_CreateFn;
		const char* m_pName;
		InterfaceReg* m_pNext;
};