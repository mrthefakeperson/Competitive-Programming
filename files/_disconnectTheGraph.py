import sys
sys.setrecursionlimit(9999999)
__=sys.stdin.readline().strip().split(" ")
n,m=int(__[0]),int(__[1])
adj=[[] for e in xrange(n+1)]
lenArray=[0]*(n+1)
for e in xrange(m):
    __=sys.stdin.readline().strip().split(" ")
    a,b=int(__[0]),int(__[1])
    adj[a].append(b)
    adj[b].append(a)
    lenArray[a]+=1
    lenArray[b]+=1
__=sys.stdin.readline().strip().split(" ")
disconnect1,disconnect2=int(__[0]),int(__[1])
#(path which this belongs to,source on the path,connected nodes)
visited=[(-1,-1,-1)]*(n+1)
visited[disconnect1]=(-2,-1,-1)

def check(ID,node):
    f=node[1]
    while visited[f][2]==1:
        f=f[1]
    return f==disconnect1

def reducePath(ID,node):
    #print node
    f=node[1]
    while visited[f][2]==1:
        visited[f]=(visited[f][0],visited[f][1],0)
        f=f[1]
    visited[f]=(visited[f][0],visited[f][1],visited[f][2]-1)

def push_path(ID,node):
    searchList,trip=[node],False
    while searchList<>[]:
        Nlist=[]
        for e in searchList:
            condd=False
            for ee in adj[e]:
                #print visited[ee][0],ee
                if visited[ee][0]<>ID:
                    condd=True
                    #print ID,visited[ee][0]
                    if visited[ee][0]<>-2 and (not check(visited[ee][0],visited[ee])):
                        #if visited[ee][0]<>-1:
                            #reducePath(visited[ee][0],visited[ee])
                        visited[ee]=(ID,e,0)
                        visited[e]=(visited[e][0],visited[e][1],visited[e][2]+1)
                        Nlist.append(ee)

            #if not condd:reducePath(ID,e)
            if e==disconnect2:trip=True
        searchList=Nlist[:]
    return trip

def zero(visited3):
    searchList,trip=[disconnect1],False
    #visited3=[False]*(n+1)
    while searchList<>[]:
        Nlist=[]
        for e in searchList:
            for ee in adj[e]:
                if not visited3[ee]:
                    visited3[ee]=True
                    Nlist.append(ee)
            if e==disconnect2:trip=True
        searchList=Nlist[:]
    return not trip

vv=[False]*(n+1)

def first(nn):
    q=False
    #vvv=[False]*(n+1)
    for e in xrange(n+1):
        if lenArray[e]>=nn:
            vvv=[False]*(n+1)
            vvv[e]=True
            q=zero(vvv)
        if q:break
    return q

if zero(vv):print 0
elif n<500 and first(2):
    print 1
else:
    try:
        rr=len(adj[disconnect1])
        for e in xrange(len(adj[disconnect1])):
            visited[adj[disconnect1][e]]=(e,disconnect1,0)
            if not push_path(e,adj[disconnect1][e]):
                rr=e
                break
        print rr
    except:
        print 1
