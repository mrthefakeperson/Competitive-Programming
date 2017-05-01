import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

s = i()
taken = {}
acc = 0
for e in xrange(len(s)):
    s_ = s[e:] + s[:e]
    if s_ not in taken:
        taken[s_] = True
        acc += 1
print acc