import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n,q=ii()
streets={}
acc=0
edges=[]
for e in xrange(n):
    a,b,c=i().split(" ")
    if a not in streets:
        streets[a]=acc
        acc+=1
    if b not in streets:
        streets[b]=acc
        acc+=1
    edges.append((streets[a],streets[b],c=="parallel"))
n=acc
adj=[[] for e in xrange(n)]
for a,b,c in edges:
    adj[a].append((b,c))
    adj[b].append((a,c))
visited=[0]*n     # 0 -> unvisited | (1,e) -> parallel to e | (0,e) -> perp to e
                  # -1 -> Waterloo
def search(node,source,state):
    if visited[node]==0:
        visited[node]=(state,source)
        for e,isParallel in adj[node]:
            if isParallel:
                search(e,source,state)
            else:
                search(e,source,not state)
    elif visited[node]==(True,source) or visited[node]==(False,source):
        if state<>visited[node][0]:
            visited[node]= -1
    #elif visited[node]== -1:
for e in xrange(n):
    if visited[e]==0:
        search(e,e,1)
if -1 in visited:
    print "Waterloo"
else:
    for e in xrange(q):
        a,b=i().split(" ")
        if a in streets and b in streets:
            aa,bb=streets[a],streets[b]
            aaa,bbb=visited[aa],visited[bb]
            if aaa[1]==bbb[1]:
                if aaa[0]==bbb[0]: print "parallel"
                else:              print "intersect"
            else:
                print "unknown"
        else: print "unknown"
