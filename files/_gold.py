import sys
_=sys.stdin.readline().strip().split(" ")
l,d=int(_[0]),int(_[1])
depthMap=[]
for e in xrange(int(_[1])):
    __=sys.stdin.readline().strip().split(" ")
    k=[int(ee) for ee in __]
    depthMap.append(k)
#visitedMap=[[False for e in xrange(int(_[0]))] for ee in xrange(int(_[1]))]
newMap=[[-1 for e in xrange(int(_[0]))] for ee in xrange(int(_[1]))]
newMap[0][0]=depthMap[0][0]
searchList=[(0,0)]
#
#for e in depthMap:print e
#for e in newMap:print e
#
while len(searchList)<>0:
    Nlist=[]
    for e in searchList:
        #if e[0]-1>=0:
            #if newMap[e[0]-1][e[1]]==-1 or newMap[e[0]-1][e[1]]>depthMap[e[0]-1][e[1]]+newMap[e[0]][e[1]]:
                #Nlist.append((e[0]-1,e[1]))
                #newMap[e[0]-1][e[1]]=depthMap[e[0]-1][e[1]]+newMap[e[0]][e[1]]
        if e[0]+1<d:
            if newMap[e[0]+1][e[1]]==-1 or newMap[e[0]+1][e[1]]>depthMap[e[0]+1][e[1]]+newMap[e[0]][e[1]]:
                Nlist.append((e[0]+1,e[1]))
                newMap[e[0]+1][e[1]]=depthMap[e[0]+1][e[1]]+newMap[e[0]][e[1]]
        if e[1]-1>=0:
            if newMap[e[0]][e[1]-1]==-1 or newMap[e[0]][e[1]-1]>depthMap[e[0]][e[1]-1]+newMap[e[0]][e[1]]:
                Nlist.append((e[0],e[1]-1))
                newMap[e[0]][e[1]-1]=depthMap[e[0]][e[1]-1]+newMap[e[0]][e[1]]
        if e[1]+1<l:
            if newMap[e[0]][e[1]+1]==-1 or newMap[e[0]][e[1]+1]>depthMap[e[0]][e[1]+1]+newMap[e[0]][e[1]]:
                Nlist.append((e[0],e[1]+1))
                newMap[e[0]][e[1]+1]=depthMap[e[0]][e[1]+1]+newMap[e[0]][e[1]]
    searchList=Nlist[:]
_=sys.stdin.readline().strip().split(" ")
print newMap[int(_[1])][int(_[0])]
