import sys

fmp = {}
def factorial(n):
    assert(n >= 0)
    if n == 0 or n == 1:
        return 1
    fmp[n] = n * factorial(n-1)
    return fmp[n]

def choose(x, m):
    return factorial(x) / factorial(m) / factorial(x-m)

mp = {}
def g(n, m, x):
    if (n, m, x) in mp:
        return mp[(n, m, x)]
    if m < 0:
        return 0
    if m == 0:
        if x < 0:
            return 0
        if x == 0:
            return factorial(n)
        mp[(n, m, x)] = (n-x) * g(n-1, 0, x-1) + (x-1) * g(n-1, 0, x-2)
        return mp[(n, m, x)]
    if m > x:
        return 0
    mp[(n, m, x)] = choose(x, m) * g(n-m, 0, x-m)
    return mp[(n, m, x)]

[n, m, k] = map(int, sys.stdin.readline().split(" "))

unused = range(1, n+1)

ans = []
poss = 0
for idx in range(n):
    for nx in unused:
        # Check if nx gives a number of possibilities > k
        currently_matching = (idx+1 == nx)
        num_matching_slots = 0
        # Loop over all slots
        for i in range(idx+1, n):
            if i+1 == nx:
                continue
            if i+1 in unused:
                num_matching_slots += 1
        poss = g(n-idx-1, m - (1 if currently_matching else 0), num_matching_slots)
        works = (poss >= k)
        
        if works:
            unused.remove(nx)
            ans.append(nx)
            if idx+1 == nx:
                # Used slot
                m -= 1
            break
        else:
            k -= poss

k -= poss
if k != 0 or len(ans) != n:
    print(-1)
else:
    print(" ".join(map(str, ans)))
