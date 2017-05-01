import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

a,b = ii()
grid = [i() for _ in xrange(a)]
smallest = -1
for e in xrange(a):
    for ee in xrange(b):
        if grid[e][ee] == 'X':
            smallest = (e,ee)
            break
    if smallest != -1: break
biggest = -1
for e in xrange(a-1, -1, -1):
    for ee in xrange(b-1, -1, -1):
        if grid[e][ee] == 'X':
            biggest = (e,ee)
            break
    if biggest != -1: break
acc = True
for e in xrange(a):
    for ee in xrange(b):
        if smallest[0] <= e and e <= biggest[0] and smallest[1] <= ee and ee <= biggest[1]:
            acc = acc and (grid[e][ee] == 'X')
        else:
            acc = acc and (grid[e][ee] == '.')
if acc: print "YES"
else: print "NO"