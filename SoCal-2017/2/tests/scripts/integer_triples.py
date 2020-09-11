import sys
import random
from math import sqrt

assert(len(sys.argv) == 4)
cases = int(sys.argv[1])
maxnum = int(sqrt(int(sys.argv[2])))
prefix = sys.argv[3]
fin = open("../in/%s.in" % prefix, 'w')
fout = open("../out/%s.out" % prefix, 'w')

for _ in range(cases):
    m = random.randint(1, maxnum)
    n = random.randint(1, maxnum)
    k = random.randint(1, maxnum)

    while n == m:
        n = random.randint(1, maxnum)

    (m, n) = (max(m, n), min(m, n))

    a = k*(m*m-n*n)
    b = k*2*m*n
    if m % 2 == 1 and n % 2 == 1:
        # get to a primitive triple
        a /= 2
        b /= 2
    fin.write("%d %d\n" % (a, b))
    if a % 2 == 1 and b % 2 == 1:
        fout.write("no\n")
    else:
        fout.write("%d\n" % ((a*b)/2))

fin.close()
fout.close()
