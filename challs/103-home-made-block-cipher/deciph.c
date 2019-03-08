#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "tools.h"

#define BUFSIZE 512

int8_t ek_inv(int8_t in, int8_t *shuf) {
	int8_t c1[4], c2[4], i;

	/* On passe par un tableau de int8_ts pour mélanger plus facilement */

	c1[0] = (in & 0x01);
	c1[1] = (in & 0x02) >> 1;
	c1[2] = (in & 0x04) >> 2;
	c1[3] = (in & 0x08) >> 3;

	/* On shuffle avec la fonction */

	for(i = 0; i < 4; i++) {
		// printf("shuf[%d]: %d\n", i, shuf[i]);
		c2[i] = c1[shuf[i]];
	}

	return (c2[3] << 3) | (c2[2] << 2) | (c2[1] << 1) | c2[0];
}

int8_t process_nibble(int8_t in, int8_t *iv, int8_t *shuf) {
	int8_t r;

	r = ek_inv(in, shuf);
	r ^= *iv;
	*iv = in;
	
	return r;
}

void process_word(int16_t in_buf, int8_t *out_buf, int8_t *iv, int8_t *shuf) {
	int8_t A, B, C, D;

	A = process_nibble((in_buf & 0x000F), iv, shuf);
	B = process_nibble((in_buf & 0x00F0) >> 4, iv, shuf);
	C = process_nibble((in_buf & 0x0F00) >> 8, iv, shuf);
	D = process_nibble((in_buf & 0xF000) >> 12, iv, shuf);

	*out_buf = reduce_word(A | (B << 4) | (C << 8) | (D << 12));
}

void process_buffer(int16_t *buf, size_t size, int8_t *iv, int8_t *shuf) {
	int8_t out_buf[BUFSIZE] = {0};
	unsigned int i;

	for(i = 0 ; i < size; i++) {
		process_word(buf[i], &out_buf[i], iv, shuf);
	}

	for(i = 0; i < 32 && (out_buf[i] == ' ' || (out_buf[i] <= 122 && out_buf[i] >= 97) || (out_buf[i] <= 90 && out_buf[i] >= 65)); i++);

	/* Si les n premiers caractères sont en ASCII */
	if(i >= 20) {
		write(STDOUT_FILENO, out_buf, size);
		write(STDOUT_FILENO, "\n", 1);
	}
}

int main(int argc, char *argv[]) {
	FILE *f;
	int r;
	unsigned int i, s;
	int16_t buf[BUFSIZE];
	int8_t iv;

	if(argc != 2) {
		fprintf(stderr, "Usage %s: <cipher file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "r");
	if(!f) {
		fclose(f);
		perror("fopen");
		return 1;
	}

	/* Bruteforce selon l'iv */
	for(i = 0; i < 16; i++) {
		// printf("IV: %d\n", i);

		/* Bruteforce selon la permutation */
		for(s = 0; s < sizeof(shufs) / sizeof(int8_t *); s++) {
			iv = i;

			// printf("Using shuffle: %d\n", s);

			while(!feof(f)) {
				r = fread(buf, sizeof(int16_t), sizeof(buf), f);

				/* On traite le buffer ici */
				process_buffer(buf, r, &iv, shufs[s]);

				if(r != sizeof(buf) * sizeof(int16_t)) {
					break;
				}
			}
			if(!feof(f)) {
				fclose(f);
				perror("fread");
				return 1;
			}

			fseek(f, 0, SEEK_SET);
		}
	}

	fclose(f);

	return 0;
}
