import sys
x=int(sys.stdin.readline().strip())
__=int(sys.stdin.readline().strip())
ll=[int(sys.stdin.readline().strip()) for e in xrange(__)]
searchList=ll[:]
coinsSoFar=1
check=True
visited={}
while check:
    Nlist=[]
    for e in searchList:
        if e==x:
            print coinsSoFar
            check=False
            break
        elif e in visited:pass
        else:
            visited[e]=True
            for ee in ll:
                Nlist.append(e+ee)
                
    searchList=Nlist[:]

    coinsSoFar+=1
