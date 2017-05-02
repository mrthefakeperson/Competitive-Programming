import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(199999)
ii=lambda:map(int,i().split(" "))

n,m=ii()
adj=[[] for e in xrange(n)]
ll=ii()
marked=[False]*n
for e in ll:
    marked[e]=True
for e in xrange(n-1):
    a,b=ii()
    adj[a].append(b)
    adj[b].append(a)
visited=[False]*n
parent=[0]*n
def dfs1(node):
    visited[node]=True
    for e in adj[node]:
        if not visited[e]:
            parent[e]=node
            dfs1(e)
dfs1(ll[0])
parent[ll[0]]=ll[0]
#print parent
visited=[True]*n
allPaths=-2
for e in ll:
    curr=e
    while visited[curr]:
        #print curr
        visited[curr]=False
        allPaths+=2
        curr=parent[curr]
cp=visited[:]
def bfs(node):
    lst=[node]
    acc=0
    while lst<>[]:
        #print lst
        nlst=[]
        for e in lst:
            visited[e]=True
            for ee in adj[e]:
                if not visited[ee]:
                    nlst.append(ee)
        if nlst==[]:
            return lst[0],acc
        lst=nlst[:]
        acc+=1
place,d=bfs(ll[0])
visited=cp
place2,d2=bfs(place)
allPaths-=d2
print allPaths