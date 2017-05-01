import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
ll=[tuple(ii()) for e in xrange(n)]
ll.sort()
accMin=99999999
destroy=[0]*(n)
used=[]
def good(pl,x,ll):
    if pl>=len(ll):
        return False
    else:
        return ll[pl]<=x
def find(x,ll):
    place,jump=-1,len(ll)
    while jump>0:
        if good(place+jump,x,ll):
            place+=jump
        jump/=2
    while good(place+1,x,ll):place+=1
    return place
ind=0
for e in ll:
    place=e[0]
    placeD=e[0]-e[1]-1
    used.append(place)
    allD=find(placeD,used)
    allD+=1
    destroyed=ind-allD
    destroyed+=destroy[allD-1]
    destroy[ind]=destroyed #+(n-ind-1)
    accMin=min(destroyed+n-ind-1,accMin)
    #print destroyed+n-ind-1
    ind+=1
#print destroy
print accMin