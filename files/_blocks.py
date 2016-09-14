import sys
def i():return sys.stdin.readline()
n=int(i())
ll=[0]+map(int,i().split(" "))+[0]
for e in xrange(1,n+2):
    ll[e]=min(ll[e],ll[e-1]+1)
for e in xrange(n,-1,-1):
    ll[e]=min(ll[e],ll[e+1]+1)
print max(ll)
