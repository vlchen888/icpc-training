from sys import stdin
from math import sqrt

lines = stdin.readlines()

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a%b)

def process(s):
    if '/' in s:
        return map(int, s.split('/'))
    return [int(s), 1]

def simplify(a):
    aa = gcd(a[0], a[1])
    a[0] /= aa
    a[1] /= aa
    return a

def issquare(n):
    low = 1
    high = n
    while low < high-1:
        mid = (low + high) / 2
        if mid*mid <=n:
            low = mid
        else:
            high = mid
    if low*low == n:
        return True
    return False

for line in lines:
    line = line.strip()
    line = line.split(' ')
    a = process(line[0])
    b = process(line[1])

    a = simplify(a)
    b = simplify(b)
    n = simplify([a[0]*b[0], 2*a[1]*b[1]])
    csq = simplify([a[0]*a[0]*b[1]*b[1]+b[0]*b[0]*a[1]*a[1], a[1]*a[1]*b[1]*b[1]])
    if n[1] != 1 or not issquare(csq[0]) or not issquare(csq[1]):
        print("no")
    else:
        print(n[0])
