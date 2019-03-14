#!/usr/bin/env python3

# Exporter le Google Doc' en csv, puis le passer au script.
# Attention il arrête de lire la liste des challs au premier saut de ligne (",,,,,," dans le csv).

from sys import argv, stderr

TIME_LIMIT = 21 * 60
PTS_LIMIT = 7
PTS_TOTAL = 20


def parse_time(time):
	t = time.split(" min ")
	if len(t) != 2:
		raise ValueError("Wrong input: {}. Expected 'xx min xx'".format(time))

	return int(t[0]) * 60 + int(t[1])


def build_time(t):
	return "{:02d} min {:02d}".format(t // 60, t % 60)


def sum_points(points):
	return sum([min(pt, PTS_LIMIT) for pt in points])


def solve(challs, path, time, points, results):
	s = sum_points(points)
	if s >= PTS_TOTAL:
		r = set()
		for p in path:
			r.add(p)

		if r not in [r[0] for r in results]:
			results.append([r, time, s, points])

		return

	for chall, data in challs.items():
		t = time + data[0]
		if t <= TIME_LIMIT:
			p = path.copy()
			p.add(chall)
			solve(challs, p, t, [points[i] + data[1 + i] for i in range(len(points))], results)


if __name__ == "__main__":
	if len(argv) < 2:
		stderr.write("Usage: {} <file>\n".format(argv[0]))
		exit(1)

	challs = {}

	with open(argv[1], "r") as f:
		f.readline()

		for line in f:
			line = line.strip().split(",")
			if len(line) != 8:
				stderr.write("Error: Wrong file format\n")
				exit(1)

			if not line[0]:
				break

			if not line[7]:
				continue

			challs[line[0]] = [parse_time(line[2])] + [int(i) for i in line[3:7]]

results = []
solve(challs, set(), 0, [0, 0, 0, 0], results)

for result, time, total, points in results:
	# print("{}: {} points, {}".format(", ".join(result), points, build_time(time)))
	print("{}\t{}\t\t{}\t{}\t{}\t{}\t{}".format(" ".join([r.split("-")[0] for r in result]), build_time(time), *points, total))
