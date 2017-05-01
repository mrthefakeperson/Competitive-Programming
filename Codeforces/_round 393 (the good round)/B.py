import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

def pillows(x, k):
    if x >= k: return x*(x+1)/2 - (x-k)*(x-k+1)/2
    else: return x*(x+1)/2+k-x

def check(n, m, k, x):
    needed = pillows(x, k) + pillows(x-1, n-k)
    return needed <= m

def src(n, m, k, a, b):
    h = (a+b) / 2
    if a == b: return a
    kk = check(n, m, k, h+1)
    if kk:
        return src(n, m, k, h+1, b)
    else:
        return src(n, m, k, a, h)
n, m, k = ii()
print src(n, m, k, 1, m)