import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
adj=[[]]
helper=[{} for e in xrange(n+1)]
m=0
for e in xrange(1,n+1):
    a=ii()[1:]
    adj.append(a)
    for ee in xrange(len(a)):
        helper[e][a[ee]]=ee
    m+=len(a)
visited=[0]*(n+1)
lastVisit=[0]*(n+1)
saveit={}   #
def query(orig,node,prev,acc):
    if (node,prev) in saveit and saveit[(node,prev)]<>-1:
        return saveit[(node,prev)]
    
    dest=adj[node][(helper[node][prev]+1)%len(adj[node])]
    if lastVisit[node]==orig:
        saveit[(node,prev)]=-1
        return query(orig,dest,node,acc+1)
    if dest==orig:
        saveit[(node,prev)]=acc
        return acc
    else:
        rr= query(orig,dest,node,acc+1)
        saveit[(node,prev)]=rr
        return rr
q=int(i())
for e in xrange(q):   #what is Q?
    t=int(i())
    accMax=0
    for e in adj[t]:
        accMax=max(accMax,query(t,e,t,1))
    print accMax+1
