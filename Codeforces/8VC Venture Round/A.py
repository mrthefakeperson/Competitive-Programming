import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
sq=i()
cnt=0
for e in xrange(n):
    for ee in xrange(e+1,n):
        v,h=0,0
        for eee in xrange(e,ee+1):
            if sq[eee]=="U":
                v+=1
            elif sq[eee]=="D":
                v-=1
            elif sq[eee]=="L":
                h+=1
            else:
                h-=1
        if v==0 and h==0:
            cnt+=1
print cnt