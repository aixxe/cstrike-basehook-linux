#pragma once

// Slightly modified version of P47R!CK & dom1n1k's pattern scanner.
inline bool Compare(const uint8_t* data, const uint8_t* pattern, const char* mask) {
	for (; *mask; ++mask, ++data, ++pattern) {
		if (*mask == 'x' && *data != *pattern) {
			return false;
		}
	}

	return *mask == 0;
}

static uintptr_t FindPattern(const char* library, const char* pattern_string, const char* mask) {
	size_t address = 0, length = 0;
	
	if (!Linker::GetLibraryInformation(library, &address, &length))
		return 0;

	const uint8_t* pattern = reinterpret_cast<const uint8_t*>(pattern_string);

	for (size_t i = 0; i < length; i++) {
		if (Compare(reinterpret_cast<uint8_t*>(address + i), pattern, mask)) {
			return address + i;
		}
	}

	return 0;
}