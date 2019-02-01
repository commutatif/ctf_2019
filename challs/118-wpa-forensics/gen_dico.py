#!/usr/bin/env python3

from sys import argv, stderr

try:
	ifile = argv[1]
	ofile = argv[2]
except:
	stderr.write("Usage: <if> <of>\n")
	exit(1)

with open(ifile, 'r') as iff:
	with open(ofile, 'w') as off:
		for line in iff:
			line = line.strip().upper()
			if len(line) == 10:
				for n in range(100):
					off.write("{}{:02d}\n".format(line, n))
