import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n,m=ii()
accMax=m
for e in xrange(n):
    a,b=ii()
    time=a+b
    if accMax==-1 or time>accMax:
        accMax=time

print accMax