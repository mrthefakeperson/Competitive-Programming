import sys
def i(): return sys.stdin.readline().strip()
n=int(i())
r,c=[False]*n,[False]*n
for e in xrange(n*n):
    ii=i().split()
    a,b=int(ii[0])-1,int(ii[1])-1
    if (not r[a]) and (not c[b]):
        r[a]=True
        c[b]=True
        print e+1