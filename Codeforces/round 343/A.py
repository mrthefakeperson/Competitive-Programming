import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
cake=[i() for e in xrange(n)]
acc=0
for e in xrange(n):
    h,v=0,0
    for ee in xrange(n):
        if cake[e][ee]=="C":
            h+=1
        if cake[ee][e]=="C":
            v+=1
    acc+=h*(h-1)+v*(v-1)
print acc/2