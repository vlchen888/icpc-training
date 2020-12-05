import random
import sys

assert(len(sys.argv) == 3)
cases = int(sys.argv[1])
maxnum = int(sys.argv[2])

for _ in range(cases):
    balls = random.randint(1, 20)
    mass = random.randint(1, maxnum*100) / 100.0
    tct = random.randint(1, maxnum*100) / 100.0
    tr = random.randint(1, maxnum*100) / 100.0
    print("%d %d %d %d" % (balls, mass, tct, tr))
