import sys
def i(): return sys.stdin.readline().strip()

n=int(i())
x,y=[],[]
for e in xrange(n):
    _=i().split(" ")
    info=(int(_[0]),int(_[1]))
    if len(x)==0:
        x.append(info[0])
    else:
        if info[0] not in x:
            x.append(info[0])
    if len(y)==0:
        y.append(info[1])
    else:
        if info[1] not in y:
            y.append(info[1])

#print x,y
if len(x)==2 and len(y)==2:
    print abs(x[0]-x[1])*abs(y[0]-y[1])
else:
    print -1