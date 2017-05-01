import sys
def i(): return sys.stdin.readline().strip()
n=int(i())
info=map(int,i().split(" "))
done=[False]*n
place=0
gotten=0
changes=-1
allDone=False
while not allDone:
    changes+=1
    allDone=True
    if place==0:
        for e in xrange(n):
            if not done[e] and info[e]<=gotten:
                gotten+=1
                done[e]=True
            if not done[e]: allDone=False
        place=n-1
    else:
        for e in xrange(n-1,-1,-1):
            if not done[e] and info[e]<=gotten:
                gotten+=1
                done[e]=True
            if not done[e]: allDone=False
        place=0
print changes