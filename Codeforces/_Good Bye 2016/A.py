import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n,k = ii()
k = 240 - k
ans = n
for e in xrange(1,n+1):
    k -= 5*e
    if k < 0:
        ans = e-1
        break
print ans