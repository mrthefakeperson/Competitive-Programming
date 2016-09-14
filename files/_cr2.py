import sys
def getThing(x,y,dMag,ll,mag):
    e=x/(5**(dMag-mag))%5
    #print ll,e
    nn=[ll[e]*5]*5
    nn[1]+=1
    nn[2]+=2
    nn[3]+=1
    if ll[e]==0:return False
    else:
        if dMag==mag:
            return ll[x%5]>y
        else:
            return getThing(x,y,dMag,nn,mag+1)

k=int(sys.stdin.readline().strip())
for e in xrange(k):
    _=sys.stdin.readline().strip().split(" ")
    if getThing(int(_[1]),int(_[2]),int(_[0]),[0,1,2,1,0],1):
        print "crystal"
    else:
        print "empty"
