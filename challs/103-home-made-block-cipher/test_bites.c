#include <stdio.h>
#include <stdint.h>
#include "tools.h"

/*int main(void) {
	uint16_t i;
	int16_t e;
	int8_t m = 1, m1, m2, A, B, C, D;

	for(i = 0; i < 8; i++) {
		m1 = m << i;
		print_bits_int8(m1);
		e = extend_byte(m1);

		A = (e & 0x000F);
		B = (e & 0x00F0) >> 4;
		C = (e & 0x0F00) >> 8;
		D = (e & 0xF000) >> 12;

		m2 = reduce_word(A | (B << 4) | (C << 8) | (D << 12));
		print_bits_int16(e);
		print_bits_int8(m2);
		puts("");
	}

	return 0;
}*/

int main(void) {
	uint16_t i;
	int16_t m = 1, m1, m2;

	for(i = 0; i < 16; i++) {
		m1 = m << i;
		print_bits_int16(m1);
		m2 = swap_bits_int16(m1);
		print_bits_int16(m2);
		puts("");
	}

	return 0;
}
