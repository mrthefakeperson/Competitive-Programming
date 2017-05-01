import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

a, b = ii()
days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
d = days[a-1]
x = d + b - 1
if x % 7 == 0: print x / 7
else: print x / 7 + 1