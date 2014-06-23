#include<stdint.h>

struct typename {
	int size;
	uint16_t data[16][16];
} Stage;

Stage teststage;

void stageinit() {
	teststage =
	{
		.size = 5,
		.data = {
			{ 0x4, 0x5, 0x1, },
			{ 0x4, 0x0, 0x0, },
			{ 0x6, 0x2, 0x3, },
		}
	};
}

