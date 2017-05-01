import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

aa=i()
bb=i()
a,b=[],[]
for e in aa:
    if e=="1":a.append(0)
    else:a.append(1)
for e in bb:
    if e=="1":b.append(0)
    else:b.append(1)
zero=[0]*(len(b)+1)
for e in xrange(len(b)):
    zero[e+1]=zero[e]+b[e]
#print zero
ind=0
tot=0
for e in a:
    dist=zero[len(b)-(len(a)-ind)+1]-zero[ind]
    #print dist
    if e==1:
        tot+=len(b)-len(a)+1-dist
    else:
        tot+=dist

    ind+=1
print tot