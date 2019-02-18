#!/usr/bin/env python3

from random import choice
from string import ascii_lowercase

# on peut deviner KEY_LENGTH en chiffrant plein de fois la même minuscule
KEY_LENGTH = 6
TXT = "aaaaaaaaaaaaaaaaaaaaaaaaaaaa"
C = [
	"g:ydkzunydkzunydkzunydkzunydkz",
	"h:zunydkzunydkzunydkzunydkzuny",
	"f:xmhalqxmhalqxmhalqxmhalqxmha"
]


def gen_random_str(n):
	return "".join(choice(ascii_lowercase) for _ in range(n))


def keep_lower_only(str):
	return "".join([c for c in str if ord("a") <= ord(c) <= ord("z")])


def shift_char(c, n):
	if ord("a") <= ord(c) <= ord("z"):
		return to_char((from_char(c) + n) % 26)
	else:
		return c


def from_char(c):
	return ord(c) - ord("a")


def to_char(i):
	return chr(i + ord("a"))


def xor(str1, str2):
	if len(str1) != len(str2):
		raise Exception("str length")
	return "".join([to_char((from_char(str1[i]) ^ from_char(str2[i])) % 26) for i in range(len(str1))])


def xor2(str1, str2):
	if len(str1) != len(str2):
		raise Exception("str length")
	return "".join([to_char((from_char(str1[i]) - from_char(str2[i])) % 26) for i in range(len(str1))])


def shift_str(str, n):
	return "".join([shift_char(c, n) for c in str])


def remove_nonce(m):
	v = from_char(m[0]) * (-1)
	return "".join([shift_char(c, v) for c in m[2:]])


if __name__ == "__main__":
	if len(TXT) < KEY_LENGTH:
		raise Exception("txt length")

	for j in range(len(C)):
		if len(C[j]) - 2 != len(TXT):
			raise Exception("C{} length".format(j))
