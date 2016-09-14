import sys
def i(): return sys.stdin.readline().strip()
_=map(int,i().split(" "))
#points (x,y) and (z,w)
x,y,z,w=_[0],_[1],_[2],_[3]
minX,minY=min(x,z),min(y,w)
maxX,maxY=max(x,z),max(y,w)
acc=0
dd=int(i())
for e in xrange(dd):
    _=map(int,i().split(" "))
    a,b,c=_[0],_[1],_[2]
    #vertical line
    if b==0:
        xC=-c/float(x)
        if xC>=minX and xC<=maxX:
            #print a,b,c
            acc+=1
    else:
        slope=-a/float(b)
        yInter=-c/float(b)
        isAbove=y>slope*x+yInter
        isAb2=w>slope*z+yInter
        if isAbove<>isAb2:
            #print a,b,c
            acc+=1
print acc
