n=input()
#thingMap={}
thingMap=["l",[]]
def checkIfInBounds(coord):
    _=coord[0]+coord[1]
    _2=n*2+1-coord[0]+coord[1]
    _3=n*2+1-coord[0]+n*2+1-coord[1]
    _4=coord[0]+n*2+1-coord[1]
    if _<=n or _2<=n or _3<=n or _4<=n:
        return False
    return True
for e in range(1,n*2+1):
    for e2 in range(1,n*2+1):
        if checkIfInBounds((e,e2)):
            print "Y",
            #thingMap[(e,e2)]=0
            thingMap[e].append(0)
        else:
            print " ",
            thingMap[e].append("N")
    thingMap[e].append(())
    print
    
    thingMap.append([])
thingMap.append([()]*(n*2))
allE=[thingMap]
count=0
for tMap in allE:
    for e2 in range(len(tMap)):
        for k2 in range(len(tMap[e])):
            if tMap[e2][k2]==0:
                e=e2+1
                k=k2
                m=tMap[:]
                print m
                m[e][k]=1
                _m=m
                if checkIfInBounds(e-1,k) and m[e-1][k]==0:
                    m[e-1][k]=1
                    count+=1
                allE.append(m)
                m=_m
                if checkIfInBounds(e+1,k) and m[e+1][k]==0:
                    m[e+1][k]=1
                    count+=1
                allE.append(m)
                m=_m
                if checkIfInBounds(e,k-1) and m[e][k-1]==0:
                    m[e][k-1]=1
                    count+=1
                allE.append(m)
                m=_m
                if checkIfInBounds(e,k+1) and m[e][k+1]==0:
                    m[e][k+1]=1
                    count+=1
                allE.append(m)
print len(allE)
