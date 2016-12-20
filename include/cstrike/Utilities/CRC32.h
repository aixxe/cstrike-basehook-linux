#pragma once

#define CRC32_INIT_VALUE 0xFFFFFFFFUL
#define CRC32_XOR_VALUE 0xFFFFFFFFUL

typedef unsigned int CRC32_t;

typedef void (*CRC32_ProcessBufferFn) (CRC32_t*, const void*, int);

extern CRC32_ProcessBufferFn CRC32_ProcessBuffer;

static void CRC32_Init(CRC32_t* crc) {
	*crc = CRC32_INIT_VALUE;
}

static void CRC32_Final(CRC32_t* crc) {
	*crc ^= CRC32_XOR_VALUE;
}