#!/usr/bin/env python3

from itertools import permutations

i = 0
for p in permutations(("0", "1", "2", "3")):
	print("int8_t shuf{}[] = {{{}}};".format(i, ", ".join(p)))
	i += 1

print("int8_t *shufs[] = {{{}}};".format(", ".join(["shuf{}".format(n) for n in range(i)])))
