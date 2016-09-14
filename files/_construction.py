import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(9999999)

nodes,edg=tuple(map(int,i().split(" ")))
adj=[[] for e in xrange(nodes+1)]
edges=[tuple(map(int,i().split(" "))) for e in xrange(edg)]
for e in edges:
    adj[e[0]].append(e[1])
    adj[e[1]].append(e[0])
    
parent=[0]*(nodes+1)
#parent[1]=1
depth=[-1]*(nodes+1)
createCycle=[]
def establish(n,deep,last):
    depth[n]=deep
    for e in adj[n]:
        if e<>last:
            if depth[e]==-1:
                parent[e]=n
                establish(e,deep+1,n)
            else:
                createCycle.append((n,e))
establish(1,0,0)
#print parent,depth
#print createCycle

belonging=range(nodes+1)
belonging[0]=1
def unravel(a):
    if belonging[a]==a:return a
    else:
        belonging[a]=unravel(belonging[a])
        return belonging[a]
for e in createCycle:
    a,b=e
    aa,bb=a,b
    while a<>b:
        #print a,b
        if depth[b]>depth[a]:
            unravel(parent[b])
            b=belonging[parent[b]]
        else:
            unravel(parent[a])
            a=belonging[parent[a]]
    while aa<>bb:
        #print aa,bb,a
        belonging[aa]=a
        belonging[bb]=a
        if depth[aa]>depth[bb]:
            aa=belonging[parent[aa]]
        else:
            bb=belonging[parent[bb]]
for e in xrange(len(belonging)):unravel(e)
#print belonging

edges=map(lambda a:(belonging[a[0]],belonging[a[1]]),edges)
edges.sort()
free=[0]*(nodes+1)
lastEdge=(-1,-1)
for e in edges:
    if not(e[0]==lastEdge[0] and e[1]==lastEdge[1]):
        lastEdge=e
        if e[0]<>e[1]:
            free[e[0]]+=1
            free[e[1]]+=1
acc=0
for e in free:
    if e==1:acc+=1
print acc-acc/2

raw_input()
