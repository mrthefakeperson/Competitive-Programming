import sys
_=sys.stdin.readline()[:-1].split(" ")
goal=(int(_[0]),int(_[1]))
K=int(sys.stdin.readline()[:-1])
allCats=[]
for e in xrange(K):
    _=sys.stdin.readline()[:-1].split(" ")
    allCats.append((int(_[1])-1,int(_[0])-1))
_=[]
for x in xrange(goal[1]):
    __=[]
    for y in xrange(goal[0]):
        __.append(0)
    _.append(__)
_[goal[1]-1][goal[0]-1]=1
_list=[(goal[1]-1,goal[0]-1)]
while (0,0) not in _list:
    _NL=[]
    if _list[0][0]-1>=0:_NL.append((_list[0][0]-1,_list[0][1]))
    for e in _list:
        if e[1]-1>=0:_NL.append((e[0],e[1]-1))
    _list=_NL
    for e in _list:
        if e not in allCats:
            #print e
            if e[0]+1>=0 and e[0]+1<goal[1]:
                _[e[0]][e[1]]+=_[e[0]+1][e[1]]
            if e[1]+1>=0 and e[1]+1<goal[0]:
                _[e[0]][e[1]]+=_[e[0]][e[1]+1]
#for e in _:print e
print _[0][0]
