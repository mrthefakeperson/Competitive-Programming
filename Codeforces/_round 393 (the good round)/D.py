import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

n = int(i())
departure = [int(i()) for _ in xrange(n)]
prices = [(-99999999, 0)]
def src(a, b, v):
    h = (a+b) / 2
    if a == b: return a
    if prices[h+1][0] <= v:
        return src(h+1, b, v)
    else:
        return src(a, h, v)
for e in departure:
    i1 = prices[src(0, len(prices)-1, e-1)][1] + 20
    i2 = prices[src(0, len(prices)-1, e-90)][1] + 50
    i3 = prices[src(0, len(prices)-1, e-1440)][1] + 120
    prices.append((e, min(min(i1, i2), i3)))
#print prices
for e in xrange(1, n+1):
    print prices[e][1] - prices[e-1][1]