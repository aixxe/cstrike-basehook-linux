#pragma once

struct Color {
	Color(int r, int g, int b, int a = 255) {
		value[0] = static_cast<unsigned char>(r);
		value[1] = static_cast<unsigned char>(g);
		value[2] = static_cast<unsigned char>(b);
		value[3] = static_cast<unsigned char>(a);
	}

	unsigned char value[4];
};