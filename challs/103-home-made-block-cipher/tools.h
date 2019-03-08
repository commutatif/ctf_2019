#include <stdint.h>
#include <stdio.h>

/* BONJOUR J'AI GÉNÉRÉ TOUTES LES PERMUTATIONS (bon, ok, avec un script python) */
int8_t shuf0[] = {0, 1, 2, 3};
int8_t shuf1[] = {0, 1, 3, 2};
int8_t shuf2[] = {0, 2, 1, 3};
int8_t shuf3[] = {0, 2, 3, 1};
int8_t shuf4[] = {0, 3, 1, 2};
int8_t shuf5[] = {0, 3, 2, 1};
int8_t shuf6[] = {1, 0, 2, 3};
int8_t shuf7[] = {1, 0, 3, 2};
int8_t shuf8[] = {1, 2, 0, 3};
int8_t shuf9[] = {1, 2, 3, 0};
int8_t shuf10[] = {1, 3, 0, 2};
int8_t shuf11[] = {1, 3, 2, 0};
int8_t shuf12[] = {2, 0, 1, 3};
int8_t shuf13[] = {2, 0, 3, 1};
int8_t shuf14[] = {2, 1, 0, 3};
int8_t shuf15[] = {2, 1, 3, 0};
int8_t shuf16[] = {2, 3, 0, 1};
int8_t shuf17[] = {2, 3, 1, 0};
int8_t shuf18[] = {3, 0, 1, 2};
int8_t shuf19[] = {3, 0, 2, 1};
int8_t shuf20[] = {3, 1, 0, 2};
int8_t shuf21[] = {3, 1, 2, 0};
int8_t shuf22[] = {3, 2, 0, 1};
int8_t shuf23[] = {3, 2, 1, 0};

int8_t *shufs[] = {shuf0, shuf1, shuf2, shuf3, shuf4, shuf5, shuf6, shuf7, shuf8, shuf9, shuf10, shuf11, shuf12, shuf13, shuf14, shuf15, shuf16, shuf17, shuf18, shuf19, shuf20, shuf21, shuf22, shuf23};


int8_t swap_bits_int8(int8_t in) {
	int8_t s = 0;

	s |= (in & 0x01) << 7;
	s |= (in & 0x02) << 5;
	s |= (in & 0x04) << 3;
	s |= (in & 0x08) << 1;
	s |= (in & 0x10) >> 1;
	s |= (in & 0x20) >> 3;
	s |= (in & 0x40) >> 5;
	s |= (in & 0x80) >> 7;

	return s;
}

int16_t swap_bits_int16(int16_t in) {
	int16_t s = 0;

	s |= (in & 0x0001) << 15;
	s |= (in & 0x0002) << 13;
	s |= (in & 0x0004) << 11;
	s |= (in & 0x0008) << 9;
	s |= (in & 0x0010) << 7;
	s |= (in & 0x0020) << 5;
	s |= (in & 0x0040) << 3;
	s |= (in & 0x0080) << 1;
	s |= (in & 0x0100) >> 1;
	s |= (in & 0x0200) >> 3;
	s |= (in & 0x0400) >> 5;
	s |= (in & 0x0800) >> 7;
	s |= (in & 0x1000) >> 9;
	s |= (in & 0x2000) >> 11;
	s |= (in & 0x4000) >> 13;
	s |= (in & 0x8000) >> 15;

	return s;
}

short extend_byte(int8_t m) {
	int16_t e = 0;

	e |= (m & 0x01);
	e |= (m & 0x02) << 3;
	e |= (m & 0x04) << 6;
	e |= (m & 0x08) << 9;
	e |= (m & 0x10) >> 2;
	e |= (m & 0x20) << 1;
	e |= (m & 0x40) << 4;
	e |= (m & 0x80) << 7;

	return e;
}

char reduce_word(int16_t e) {
	int8_t m = 0;

	m |= (e & 0x0001);
	m |= (e & 0x0010) >> 3;
	m |= (e & 0x0100) >> 6;
	m |= (e & 0x1000) >> 9;
	m |= (e & 0x0004) << 2;
	m |= (e & 0x0040) >> 1;
	m |= (e & 0x0400) >> 4;
	m |= (e & 0x4000) >> 7;

	return m;
}

void _print_bits(unsigned char in) {
	char a[8];

	a[0] = (in & 0x01);
	a[1] = (in & 0x02) >> 1;
	a[2] = (in & 0x04) >> 2;
	a[3] = (in & 0x08) >> 3;
	a[4] = (in & 0x10) >> 4;
	a[5] = (in & 0x20) >> 5;
	a[6] = (in & 0x40) >> 6;
	a[7] = (in & 0x80) >> 7;

	printf("%d%d%d%d %d%d%d%d ", a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0]);
}

void print_bits_int8(int8_t in) {
	_print_bits(in);
	puts("");
}

void print_bits_int16(int16_t in) {
	_print_bits((in & 0xFF00) >> 8);
	_print_bits(in & 0xFF);
	puts("");
}
