#include <vector>
#include <link.h>
#include <string.h>

#include "Linker.h"

struct dlinfo_t {
	// Full path to shared library on filesystem.
	const char* library = nullptr;

	// Absolute 'start address' in memory.
	uintptr_t address = 0;

	// Size in memory - accuracy is questionable.
	size_t size = 0;
};

std::vector<dlinfo_t> libraries;

bool Linker::GetLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
	if (libraries.size() == 0) {
		dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
			dlinfo_t library_info = {};
			
			library_info.library = info->dlpi_name;
			library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
			library_info.size = info->dlpi_phdr[0].p_memsz;
			
			libraries.push_back(library_info);

			return 0;
		}, nullptr);
	}

	for (const dlinfo_t& current: libraries) {
		if (!strcasestr(current.library, library))
			continue;

		if (address)
			*address = current.address;

		if (size)
			*size = current.size;

		return true;
	}

	return false;
}