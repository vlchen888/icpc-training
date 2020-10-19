import sys
import random
from math import sqrt

assert(len(sys.argv) == 4)
cases = int(sys.argv[1])
maxnum = int(sqrt(int(sys.argv[2])))
prefix = sys.argv[3]
fin = open("../in/%s.in" % prefix, 'w')
fout = open("../out/%s.out" % prefix, 'w')

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a%b)

def simplify(a):
    aa = gcd(a[0], a[1])
    a[0] /= aa
    a[1] /= aa
    return a

for _ in range(cases):
    m = random.randint(1, maxnum)
    n = random.randint(1, maxnum)
    k = random.randint(1, maxnum)
    denom = random.randint(2, maxnum)

    while n == m:
        n = random.randint(1, maxnum)

    (m, n) = (max(m, n), min(m, n))

    a = k*(m*m-n*n)
    b = k*2*m*n
    if m % 2 == 1 and n % 2 == 1:
        # get to a primitive triple
        a /= 2
        b /= 2

    # sometimes multiply top and bottom of one fraction by a random number
    multa = 1
    multb = 1
    if random.randint(1, 2) == 2:
        multa = random.randint(1, int(sqrt(maxnum)))
    if random.randint(1, 2) == 2:
        multb = random.randint(1, int(sqrt(maxnum)))

    fin.write("%d/%d %d/%d\n" % (a*multa, denom*multa, b*multb, denom*multb))
    if a % 2 == 1 and b % 2 == 1:
        fout.write("no\n")
    else:
        if simplify([a*b, 2*denom*denom])[1] == 1:
            fout.write("%d\n" % ((a*b)/(2*denom*denom)))
        else:
            fout.write("no\n")

fin.close()
fout.close()
