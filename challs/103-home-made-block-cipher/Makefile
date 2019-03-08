CC = gcc
CFLAGS += -Wall -Wextra -pedantic -std=c11 -g

.PHONY: clean

all: ciph deciph test_bites

ciph: ciph.c tools.h
	$(CC) -o $@ $< $(CFLAGS)

deciph: deciph.c tools.h
	$(CC) -o $@ $< $(CFLAGS)

test_bites: test_bites.c tools.h
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf deciph ciph test_bites 2>/dev/null
