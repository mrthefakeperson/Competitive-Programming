import sys
def i(): return sys.stdin.readline().strip()
_=map(int,i().split(" "))
limit,buildings,roads,dests=_[0],_[1],_[2],_[3]
allDests=[]
for e in xrange(dests): allDests.append(int(i()))
adj=[[] for e in xrange(buildings+2)]
for e in xrange(roads):
    _=map(int,i().split(" "))
    a,b,c=_[0],_[1],_[2]
    adj[a].append((b,c))
visited=[-1]*(buildings+2)
searchList=[(0,0)]
while searchList<>[]:
    Nlist=[]
    for e_ in searchList:
        node,dist=e_[0],e_[1]
        if visited[node]== -1 or visited[node]>dist:
            visited[node]=dist
            for nnode in adj[node]:
                Nlist.append((nnode[0],nnode[1]+dist))
    searchList=Nlist[:]

acc=0
for e in allDests:
    if e>=len(visited): print e
    if visited[e]<limit and visited[e]<> -1:
        acc+=1
print acc
