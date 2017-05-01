import sys
def i():return sys.stdin.readline()
n=int(i())
ll=map(int,i().split(" "))
selff=ll[0]
t=0
others=ll[1:]
while selff<=max(others):
    mx,mI=0,0
    for e in xrange(len(others)):
        if others[e]>mx:
            mI=e
            mx=others[e]
    others[mI]-=1
    selff+=1
    t+=1
    #print others
print t