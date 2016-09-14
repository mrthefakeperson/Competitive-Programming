import sys
_k=int(sys.stdin.readline().strip())
for eX in xrange(_k):
    __=sys.stdin.readline().strip().split(" ")
    c,r=int(__[0]),int(__[1])
    room=[]
    start,goal=(0,0),(0,0)
    for e in xrange(r):
        _=sys.stdin.readline().strip()
        if "W" in _:
            goal=(e,_.find("W"))
        if "C" in _:
            start=(e,_.find("C"))
        k=[ee for ee in _]
        room.append(k)
    searchList=[start]
    steps=0
    while steps<60 and room[goal[0]][goal[1]]=="W":
        steps+=1
        Nlist=[]
        for e in searchList:
            if e[0]-1>=0:
                if room[e[0]-1][e[1]]<>"X":
                    Nlist.append((e[0]-1,e[1]))
                    room[e[0]-1][e[1]]="X"
            if e[0]+1<r:
                if room[e[0]+1][e[1]]<>"X":
                    Nlist.append((e[0]+1,e[1]))
                    room[e[0]+1][e[1]]="X"
            if e[1]-1>=0:
                if room[e[0]][e[1]-1]<>"X":
                    Nlist.append((e[0],e[1]-1))
                    room[e[0]][e[1]-1]="X"
            if e[1]+1<c:
                if room[e[0]][e[1]+1]<>"X":
                    Nlist.append((e[0],e[1]+1))
                    room[e[0]][e[1]+1]="X"
        searchList=Nlist[:]
    if steps>=60:print "#notworth"
    else:print steps
