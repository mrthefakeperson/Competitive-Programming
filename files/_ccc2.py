import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

t=int(i())
n=int(i())
l1=ii()
l2=ii()
l1.sort()
l2.sort()
#print l1,l2
acc=0
if t==1:
    for e in xrange(n):
        acc+=max(l1[e],l2[e])
else:
    ll=l1+l2
    ll.sort()
    acc=sum(ll[n:])
print acc
