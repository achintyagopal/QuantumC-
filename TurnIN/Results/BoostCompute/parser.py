import numpy as np 
import sys

if len(sys.argv) != 2:
    print "Need 1 cmd line arg, filename"

filename = sys.argv[1]

median_times = []
with open(filename, 'r') as f:
    i = 0
    times = []
    for line in f:
        tokens = line.strip().split()
        if len(tokens) == 0:
            continue
        if tokens[0] != "real":
            continue

        time = float(tokens[1][2:-1])
        if i == 20:
            median_times.append(np.median(np.array(times)))
            times = []
            i = 0

        times.append(time)
        i += 1

median_times.append(np.mean(np.array(times)))

filename = filename + "-parsed"
with open(filename, 'w') as f:
    for t in median_times:
        f.write(str(t) + "\n")
