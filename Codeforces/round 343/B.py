import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
presentM,presentF=[0]*400,[0]*400
for e in xrange(n):
    _=i().split(" ")
    a,b=int(_[1]),int(_[2])
    if _[0]=="M":
        for e in xrange(a,b+1):
            presentM[e]+=1
    else:
        for e in xrange(a,b+1):
            presentF[e]+=1
accMax=0
for e in xrange(1,367):
    accMax=max(accMax,min(presentM[e],presentF[e]))

print accMax*2