import sys
k=int(sys.stdin.readline()[:-1])
minn,maxx=[0,0],[0,0]
for e in xrange(k-1):
    _=sys.stdin.readline()[:-1].split(" ")
    on,off=int(_[0]),int(_[1])
    if e==0:
        minn[0]+=on
        maxx[0]+=on
    else:
        minn[0]-=off
        if minn[0]<0:
            minn[1]+=minn[0]
            minn[0]=0
        maxx[1]-=off
        if maxx[1]<0:
            maxx[0]+=maxx[1]
            maxx[1]=0
        minn[1]+=on
        maxx[1]+=on
print minn[0]
print maxx[0]
