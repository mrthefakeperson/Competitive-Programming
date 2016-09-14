import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

def into(node,sig,visited,ll):
    a=node
    passed=[]
    while visited[a]==0:
        passed.append(a)
        visited[a]=sig
        a=ll[a]
    for e in passed:
        visited[e]=visited[a]
for e_ in xrange(2):
    n=int(i())
    ll=[(int(i())-1) for e in xrange(n)]
    visited=[0]*n
    for e in xrange(n):
        into(e,e+1,visited,ll)
    visited.sort()
    acc,prev=0,0
    for e in visited:
        if prev<>e:
            acc+=1
        prev=e
    print acc,
        
    
