import sys
_=int(sys.stdin.readline().strip().split(" ")[1])
ratings=[[],[],[],[],[],[],[],[],[],[],[]]
__=sys.stdin.readline().strip().split(" ")
for e in xrange(0,len(__)):
    #print int(__[e])
    ratings[int(__[e])].append(e+1)
def bSearc(where,what,inWhat,jump):
    #print where,jump
    if inWhat[where]>=what and inWhat[where-1]<what:return where
    elif what>=inWhat[where]:
        if jump==1:
            return bSearch(where+1,what,inWhat,1)
        else:
            return bSearch(where+jump/2,what,inWhat,jump/2)
    else:
        if jump==1:
            return bSearch(where-1,what,inWhat,1)
        else:
            return bSearch(where-jump/2,what,inWhat,jump/2)
def bSearch(where,what,inWhat,jump):
    if len(inWhat)==0:return -1
    elif inWhat[0]>=what:return 0
    elif inWhat[-1]<what:return len(inWhat)
    else:
        return bSearc(where,what,inWhat,jump)
#print ratings
#print bSearch(1,7,[1,3,7],1)
for ee in xrange(_):
    k=sys.stdin.readline().split(" ")
    for e in xrange(10,1,-1):
        #print k[0],bSearch(len(ratings[e])/2-1,int(k[0])-1,ratings[e],len(ratings[e])/2),":",
        #print k[1],bSearch(len(ratings[e])/2-1,int(k[1]),ratings[e],len(ratings[e])/2)
        _s=len(ratings[e])-(bSearch(len(ratings[e])/2-1,int(k[1])+1,ratings[e],len(ratings[e])/2)-\
                   bSearch(len(ratings[e])/2-1,int(k[0]),ratings[e],len(ratings[e])/2))
        if _s<>0:
            print e,_s
            break
#_=sys.stdin.readline().strip().split(" ")
#ll=[int(e) for e in _]
#print bSearch(len(ll)/2-1,input(),ll,len(ll)/2)
