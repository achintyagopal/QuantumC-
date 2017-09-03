import sys

if len(sys.argv) != 2:
    print "Need 1 cmd line arg, filename"

filename = sys.argv[1]


with open(filename, 'r') as f:
    i = 0
    for line in f:
        tokens = line.strip().split()
        print(tokens[0])
        if len(tokens) == 0:
            continue
        if tokens[0] != "real":
            continue

        print(tokens[1])