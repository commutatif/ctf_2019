#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "tools.h"

#define BUFSIZE 256

int8_t ek(int8_t in) {
	int8_t c1[4], c2[4], i;

	/* On passe par un tableau de chars pour mélanger plus facilement */

	c1[0] = (in & 0x01);
	c1[1] = (in & 0x02) >> 1;
	c1[2] = (in & 0x04) >> 2;
	c1[3] = (in & 0x08) >> 3;

	/* On shuffle avec la fonction */

	for(i = 0; i < 4; i++) {
		c2[i] = c1[shuf16[i]];
	}

	return (c2[3] << 3) | (c2[2] << 2) | (c2[1] << 1) | c2[0];
}

int8_t process_nibble(int8_t in, int8_t *iv) {
	*iv = ek(*iv ^ in);
	return *iv;
}

void process_word(int16_t *out_buf, int16_t e, int8_t *iv) {
	int8_t A, B, C, D;

	A = process_nibble(e & 0x000F, iv);
	B = process_nibble((e & 0x00F0) >> 4, iv);
	C = process_nibble((e & 0x0F00) >> 8, iv);
	D = process_nibble((e & 0xF000) >> 12, iv);

	*out_buf = A | (B << 4) | (C << 8) | (D << 12);
}

void cipher_buffer(int16_t *out_buf, int8_t *in_buf, size_t size, int8_t *iv) {
	unsigned int i;
	short e;

	for(i = 0 ; i < size; i++) {
		e = extend_byte(in_buf[i]);
		process_word(&out_buf[i], e, iv);
	}
}

int main(int argc, char *argv[]) {
	FILE *fin, *fout;
	int r, w;
	int8_t in_buf[BUFSIZE], iv = 13;
	int16_t out_buf[BUFSIZE];

	if(argc != 3) {
		fprintf(stderr, "Usage %s: <in plaintext file> <out cipher file>\n", argv[0]);
		return 1;
	}

	fin = fopen(argv[1], "r");
	if(!fin) {
		perror("fopen");
		return 1;
	}

	fout = fopen(argv[2], "w");
	if(!fout) {
		fclose(fin);
		perror("fopen");
		return 1;
	}

	while(!feof(fin)) {
		r = fread(in_buf, sizeof(int8_t), sizeof(in_buf), fin);

		/* On chiffre le buffer ici */
		cipher_buffer(out_buf, in_buf, r, &iv);

		w = fwrite(out_buf, sizeof(int16_t), r, fout);
		if(w != r) {
			perror("fwrite");
			fclose(fin);
			fclose(fout);
			return 1;
		}

		/* Si on a lu moins que la taille du buffer, on est en fin de fichier ou il y a eu une erreur */
		if(r != sizeof(in_buf) * sizeof(int8_t)) {
			break;
		}
	}
	if(!feof(fin)) {
		fclose(fin);
		fclose(fout);
		perror("fread");
		return 1;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}
