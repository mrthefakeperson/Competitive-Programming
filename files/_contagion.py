
def path(nde,toVisit,arrival,d):
    node=nde
    while node>=0:
        toVisit.remove(node)
        accMin,acc=-1,-1
        for e in toVisit:
            dist=(d[e][0]-d[node][0])*(d[e][0]-d[node][0])+(d[e][1]-d[node][1])*(d[e][1]-d[node][1])
            if arrival[e]==-1 or arrival[node]+dist<arrival[e]:
                arrival[e]=arrival[node]+dist
            if accMin==-1 or arrival[e]<accMin:
                accMin=arrival[e]
                acc=e
        node=acc
def good(place,ll,thing):
    if place>len(ll):return False
    else: return thing>=ll[place-1]
def find(x,ll):
    place=0
    jump=len(ll)
    while jump>0:
        if good(place+jump,ll,x):
            place+=jump
        jump/=2
    while good(place+1,ll,x):place+=1
    return place

def main():
    import sys
    i=lambda:sys.stdin.readline().strip()
    pipefw=lambda n,f:f(n)
    sys.setrecursionlimit(999999)

#just reading input, nothing sketchy here
    n=pipefw(i(),int)
    countries=[tuple(map(int,i().split(" "))) for _ in xrange(n)]
    start=pipefw(i(),int)-1
    q=pipefw(i(),int)
    queries=[pipefw(i(),int) for _ in xrange(q)]

#set up the djikstras
    enum=lambda e:xrange(len(e))

    arrival=[-1]*n      #time arrived for each country
    arrival[start]=0
#visited=[False]*n
    toVisit=range(n)

#do it
    path(start,toVisit,arrival,countries)

#print adj
#print arrival
    arrival.sort()
    for e in queries:
        print find(e,arrival)
#print find(input(),[(1,0),(4,0),(5,0),(6,0),(7,0),(11,0),(13,0)])
main()
