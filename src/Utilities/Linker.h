#pragma once

namespace Linker {
	// Iterate loaded shared libraries and optionally return base address and size.
	bool GetLibraryInformation(const char*, uintptr_t* = nullptr, size_t* = nullptr);
}