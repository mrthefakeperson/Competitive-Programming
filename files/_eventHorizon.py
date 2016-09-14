import sys
sys.setrecursionlimit(99999999)
ii=lambda:map(int,sys.stdin.readline().split(" "))

n,m=ii()
allEdges=map(lambda a:(a[0]-1,a[1]-1),[tuple(ii()) for e in xrange(m)])
adj=[[] for e in xrange(n)]
for a,b in allEdges:
    adj[a].append(b)
    adj[b].append(a)
taken=[0]*n
forward=[[0]*n for e in xrange(n)]
def pathToMin(node,visited):
    visited[node]=True
    accMin=(taken[node],[])
    for e in adj[node]:
        if forward[node][e]>0 and not visited[e]:
            accMin=min(accMin,pathToMin(e,visited))
    accMin[1].append(node)
    return accMin
for a,b in allEdges:
    aa,bb=pathToMin(a,[False]*n),pathToMin(b,[False]*n)
    if aa<bb:
        forward[a][b]+=1
    else:
        forward[b][a]+=1
    using=min(aa,bb)[1]
    taken[using[0]]+=1
    for ee in xrange(len(using)-1):
        forward[using[ee]][using[ee+1]]+=1
        forward[using[ee+1]][using[ee]]-=1
print max(taken)


