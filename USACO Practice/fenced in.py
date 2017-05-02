import sys
sys.stdin=open("fencedin.in","r")
pr=open("fencedin.out","w")
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

maxX,maxY,n,m=ii()
verticalFences=[int(i()) for e in xrange(n)]
horizontalFences=[int(i()) for e in xrange(m)]
vEdges,hEdges=[],[]
prev=0
verticalFences.sort()
horizontalFences.sort()
for e in verticalFences:
    vEdges.append(e-prev)
    prev=e
vEdges.append(maxX-prev)
prev=0
for e in horizontalFences:
    hEdges.append(e-prev)
    prev=e
hEdges.append(maxY-prev)
allEdges=map(lambda a:(a,True),vEdges)+map(lambda a:(a,False),hEdges)
allEdges.sort()
#print allEdges

usedV,usedH=0,0
acc=0
for e,isV in allEdges:
    if isV:
        usedV+=1
        if usedV==1:
            acc+=m*e
        elif usedH==0:
            acc+=m*e
        else:
            acc+=(m-usedH+1)*e
    else:
        usedH+=1
        if usedH==1:
            acc+=n*e
        elif usedV==0:
            acc+=n*e
        else:
            acc+=(n-usedV+1)*e
#print acc
pr.write(str(acc))

pr.close()